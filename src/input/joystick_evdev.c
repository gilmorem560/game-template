#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev/libevdev.h>

static int joystick_fd = 0;
static struct libevdev *joystick = NULL;

void joystick_init(void)
{
	/* get fd */
	if ((joystick_fd = open("/dev/input/js1", O_RDWR)) == 0) {
		fputs("joystick_evdev: init fd failure\n", stderr);
		return;
	}

	/* init struct */
	if ((joystick = libevdev_new()) == NULL) {
		fputs("joystick_evdev: init failure\n", stderr);
		close(joystick_fd);
		return;
	}

	if (fsync(joystick_fd) != 0) {
		fprintf(stderr, "joystick_evdev: init flush failure: %s\n", strerror(errno));
		close(joystick_fd);
		return;
	}

	/* attach */
	if (libevdev_set_fd(joystick, joystick_fd) < 0) {
		fputs("joystick_evdev: init fd failure: %s\n", stderr);
		libevdev_free(joystick);
		close(joystick_fd);
		return;
	}

	/* success! */
	puts("joystick_evdev: paired\n");

	return;
}

void joystick_read(void)
{
	struct input_event event;

	while (libevdev_has_event_pending(joystick)) {
		switch(libevdev_next_event(joystick, LIBEVDEV_READ_FLAG_NORMAL, &event)) {
		case LIBEVDEV_READ_STATUS_SUCCESS:
			puts("joystick_read: success\n");
			break;
		case LIBEVDEV_READ_STATUS_SYNC:
			break;
		default:
			fputs("joystick_read: libevdev_next_event failure\n", stderr);
			break;
		}
	}

	return;
}

void joystick_free(void)
{
	/* cleanup */
	if (joystick != NULL)
		libevdev_free(joystick);

	/* free fd */
	if (joystick_fd != 0) {
		close(joystick_fd);
	}

	return;
}

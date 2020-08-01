#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev/libevdev.h>

#include "joystick.h"

static int joystick_fd = 0;
static struct libevdev *joystick = NULL;

void joystick_init(void)
{
	int joystick_rc = 1;
	pad_pressed = 0;
	pad_held = 0;
	/* get fd */
	if ((joystick_fd = open("/dev/input/event8", O_RDWR | O_NONBLOCK)) == 0) {
		fputs("joystick_evdev: init fd failure\n", stderr);
		return;
	}

	/* init struct */
	if ((joystick_rc = libevdev_new_from_fd(joystick_fd, &joystick)) < 0) {
		perror("joystick_evdev: init failure");
		close(joystick_fd);
		return;
	}

	/* check capabilities */
	if (!libevdev_has_event_type(joystick, EV_SYN)
	||	!libevdev_has_event_type(joystick, EV_KEY)
	||	!libevdev_has_event_type(joystick, EV_ABS)) {
		fputs("joystick_evdev: device type failure\n", stderr);
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
	pad_pressed = 0;
	struct input_event event;

	while (libevdev_has_event_pending(joystick)) {
		switch(libevdev_next_event(joystick, LIBEVDEV_READ_FLAG_NORMAL, &event)) {
		case LIBEVDEV_READ_STATUS_SUCCESS:
			switch(event.type) {
			case EV_KEY:
				switch (event.code) {
				case BTN_THUMB2:
					pad_pressed |= event.value << PAD_B;
					pad_held ^= event.value << PAD_B;
					break;
				case BTN_BASE4:
					pad_pressed |= event.value << PAD_START;
					pad_held ^= event.value << PAD_START;
					break;
				case BTN_BASE5:
					pad_pressed |= event.value << PAD_SELECT;
					pad_held ^= event.value << PAD_SELECT;
					break;
				default:
					break;
				}
				break;
			case EV_ABS:
				fprintf(stderr, "%s %d\n", libevdev_event_code_get_name(event.type, event.code), event.value);
				switch (event.code) {
				case ABS_X:
					if (event.value == 0) {
						pad_pressed |= 1 << PAD_LEFT;
						pad_held |= 1 << PAD_LEFT;
					} else if (event.value == 255) {
						pad_pressed |= 1 << PAD_RIGHT;
						pad_held |= 1 << PAD_RIGHT;
					} else if (event.value == 127) {
						pad_held &= ~((1 << PAD_RIGHT) | (1 << PAD_LEFT));
					}
					break;
				case ABS_Y:
					if (event.value == 0) {
						pad_pressed |= 1 << PAD_UP;
						pad_held |= 1 << PAD_UP;
					} else if (event.value == 255) {
						pad_pressed |= 1 << PAD_DOWN;
						pad_held |= 1 << PAD_DOWN;
					} else if (event.value == 127) {
						pad_held &= ~((1 << PAD_DOWN) | (1 << PAD_UP));
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
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

/*
 * main - entry point
 */
#ifndef _WIN32
#include "../config.h"
#endif  /* _WIN32 */

/* game modes */
#include "modes/modes.h"

/* defaults */
#define	INITIAL_GM	GM_ACTOR_TEST

#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
	#ifndef NDEBUG
	/* debugging can choose games 1-9 on command line */
    if (argc > 1) {
		if (strlen(argv[1]) > 1 || !isdigit((int) argv[1][0])) {
			fprintf(stderr, "Malformed modenum: %s\n", argv[1]);
			return EXIT_FAILURE;
		}
		game_mode = atoi(argv[1]);
    } else {
		game_mode = INITIAL_GM;
	}
	#else
	game_mode = INITIAL_GM;
	#endif /* NDEBUG */

    key = 0;    /* initialize key bitfield here for now */
    mouse_moved_x = false;
	mouse_moved_y = false;
	isfullscreen = true;
    quit = false;

	/* start in debug mode */
	debug_init;

    /* initialize OpenGL for X11 */
    glxinit();

    /* prepare OpenGL assets */
    switch (game_mode) {
	case GM_ACTOR_TEST:
		actor_test_init();
		break;
    default:
        break;
    }

    /* main loop */
    while (!quit) {
		#ifndef NDEBUG
		/* can uncapture mouse when debugging, need to display cursor too */
		if (debug_cursor_changed) {
			if (!mouse_captured)
				/* return visible cursor */
				XUndefineCursor(dpy, win);
			else
				/* associate it */
				XDefineCursor(dpy, win, cursor);
			debug_cursor_changed = false;
		}
		#endif /* NDEBUG */
		
        /* begin processing events */
		glxevent(dpy);

		switch (game_mode) {
		case GM_ACTOR_TEST:
			/* run mode routine */
			actor_test_routine();
			/* process next frame */
			actor_test_render();
			/* process movement */
			actor_test_input();
			break;
		default:
			fprintf(stderr, "Unknown game mode: %d\n", game_mode);
			quit = true;
			break;
		}
    }

    /* unload OpenGL assets */
    switch (game_mode) {
	case GM_ACTOR_TEST:
		actor_test_free();
		break;
    default:
        break;
    }

    /* close OpenGL for X11 */
    glxfree();

    return EXIT_SUCCESS;
}
#else   /* _WIN32 */
/*
 * WinMain - windows entry point
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	#ifndef NDEBUG
	/* debugging can choose games 1-9 on command line */
	if (__argc > 1) {
		if (strlen(__argv[1]) > 1 || !isdigit((int) __argv[1][0])) {
			fprintf(stderr, "Malformed modenum: %s\n", __argv[1]);
			return EXIT_FAILURE;
		}
		game_mode = atoi(__argv[1]);
	} else {
		game_mode = INITIAL_GM;
	}
	#else
	game_mode = INITIAL_GM;
	#endif /* NDEBUG */

	key = 0;    /* initialize key bitfield here for now */
	mouse_moved_x = false;
	mouse_moved_y = false;
	isfullscreen = true;
	quit = false;

	debug_init;

    /* initialize OpenGL for WinAPI */
    wglinit(hInstance, nShowCmd, wndproc);

    /* prepare OpenGL assets */
    switch (game_mode) {
	case GM_ACTOR_TEST:
		actor_test_init();
		break;
    default:
        break;
    }

    /* main loop */
    while (!quit) {
		#ifndef NDEBUG
		/* TODO: can uncapture mouse when debugging, need to display cursor too */
		if (debug_cursor_changed) {
			if (!mouse_captured)
				/* return visible cursor */
				ShowCursor(FALSE);
			else
				/* associate it */
				ShowCursor(TRUE);
			debug_cursor_changed = false;
		}
		#endif /* NDEBUG */

        /* begin processing events */
        wglevent(wnd);

		switch (game_mode) {
		case GM_ACTOR_TEST:
			/* run mode routine */
			actor_test_routine();
			/* process next frame */
			actor_test_render();
			/* process movement */
			actor_test_input();
			break;
		default:
			fprintf(stderr, "Unknown game mode: %d\n", game_mode);
			quit = true;
			break;
		}
    }

    /* unload OpenGL assets */
    switch (game_mode) {
	case GM_ACTOR_TEST:
		actor_test_free();
		break;
    default:
        break;
    }

    /* close OpenGL for WinAPI */
    wglfree(hInstance);

    return EXIT_SUCCESS;
}
#endif  /* _WIN32 */

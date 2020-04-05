/*
 * main - entry point
 */
#ifndef _WIN32
#include "../config.h"
#endif  /* _WIN32 */

/* game modes */
#include "modes/modes.h"

/* defaults */
#define	INITIAL_GM	GM_DIAMONDS

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
	#ifndef NDEBUG
	/* debugging can uncapture pointer */
	mouse_captured = true;
	debug_cursor_changed = false;
	#endif

    /* initialize OpenGL for X11 */
    glxinit();

    /* prepare OpenGL assets */
    switch (game_mode) {
    case GM_DIAMONDS:
        diamond_init();
        break;
    case GM_MAP:
	    map_init();
	    break;
	case GM_SANDBOX:
		sandbox_init();
		break;
	case GM_STAGE:
		stage_init();
		break;
	case GM_SCENE_TEST:
		scene_test_init();
		break;
    default:
        break;
    }

    /* main loop */
    while (!quit) {
		#ifndef NDEBUG
		/* can uncapture mouse when debugging, need to display cursor too */
		if (debug_cursor_changed) {
			if (!mouse_captured) {
				/* return visible cursor */
				XUndefineCursor(dpy, win);
			} else {
				/* associate it */
				XDefineCursor(dpy, win, cursor);
			}
			debug_cursor_changed = false;
		}
		#endif /* NDEBUG */
		
        /* begin processing events */
		glxevent(dpy);

		switch (game_mode) {
		case GM_DIAMONDS:
			/* process next frame */
			diamond_render();
			/* process movement */
			diamond_input();
            /* run mode routine */
            diamond_routine();
			break;
		case GM_MAP:
			/* process next frame */
			map_render();
			/* process movement */
			map_input();
            /* run mode routine */
            map_routine();
			break;
		case GM_SANDBOX:
			/* process next frame */
			sandbox_render();
			/* process movement */
			sandbox_input();
            /* run mode routine */
            sandbox_routine();
			break;
		case GM_STAGE:
			/* process next frame */
			stage_render();
			/* process movement */
			stage_input();
			/* run mode routine */
			stage_routine();
			break;
		case GM_SCENE_TEST:
			/* process next frame */
			scene_test_render();
			/* process movement */
			scene_test_input();
			/* run mode routine */
			scene_test_routine();
			break;
		default:
			fprintf(stderr, "Unknown game mode: %d\n", game_mode);
			quit = true;
			break;
		}
    }

    /* unload OpenGL assets */
    switch (game_mode) {
    case GM_DIAMONDS:
        diamond_free();
        break;
    case GM_MAP:
        map_free();
		break;
	case GM_SANDBOX:
		sandbox_free();
		break;
	case GM_STAGE:
		stage_free();
		break;
	case GM_SCENE_TEST:
		scene_test_free();
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
    quit = false;

    /* initialize OpenGL for WinAPI */
    wglinit(hInstance, nShowCmd, wndproc, XRES, YRES);

    /* prepare OpenGL assets */
    switch (game_mode) {
    case GM_DIAMONDS:
        diamond_init();
        break;
    case GM_MAP:
        map_init();
        break;
    case GM_SANDBOX:
        sandbox_init();
        break;
	case GM_STAGE:
		stage_init();
		break;
	case GM_SCENE_TEST:
		scene_test_init();
		break;
    default:
        break;
    }

    /* main loop */
    while (!quit) {
        /* begin processing events */
        wglevent(wnd);

        switch (game_mode) {
        case GM_DIAMONDS:
            /* process next frame */
            diamond_render();
            /* process movement */
            diamond_input();
            /* run mode routine */
            diamond_routine();
            break;
        case GM_MAP:
            /* process next frame */
            map_render();
            /* process input */
            map_input();
            /* run mode routine */
            map_routine();
            break;
        case GM_SANDBOX:
            /* process next frame */
            sandbox_render();
            /* process input */
            sandbox_input();
            /* run mode routine */
            sandbox_routine();
            break;
		case GM_STAGE:
			/* process next frame */
			stage_render();
			/* process input */
			stage_input();
			/* run mode routine */
			stage_routine();
			break;
		case GM_SCENE_TEST:
			/* process next frame */
			scene_test_render();
			/* process input */
			scene_test_input();
			/* run mode routine */
			scene_test_routine();
			break;
        default:
            fprintf(stderr, "Unknown game mode: %d\n", game_mode);
            quit = true;
            break;
        }
    }

    /* unload OpenGL assets */
    switch (game_mode) {
    case GM_DIAMONDS:
        diamond_free();
        break;
    case GM_MAP:
        map_free();
        break;
    case GM_SANDBOX:
        sandbox_free();
        break;
	case GM_STAGE:
		stage_free();
		break;
	case GM_SCENE_TEST:
		scene_test_free();
		break;
    default:
        break;
    }

    /* close OpenGL for WinAPI */
    wglfree(hInstance);

    return EXIT_SUCCESS;
}
#endif  /* _WIN32 */

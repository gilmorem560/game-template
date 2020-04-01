/*
 * main - entry point
 */
#include <ctype.h>

#define XRES    640
#define YRES    480

#ifndef _WIN32
#include "../config.h"
#endif  /* _WIN32 */

/* graphics handler */
#include "graphics/contexts/glcontext.h"

/* input handler */
#include "input/input.h"

/* basic objects */
#include "graphics/primitives/coord.h"
#include "graphics/primitives/prim.h"

/* composite objects */
#include "graphics/objects/hedrons.h"

/* game modes */
#include "modes/modes.h"

#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Format: %s <modenum>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (strlen(argv[1]) > 1 || !isdigit((int) argv[1][0])) {
        fprintf(stderr, "Malformed modenum: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    game_mode = atoi(argv[1]);

    if (game_mode < GM_DIAMONDS || game_mode > GM_SANDBOX) {
        fprintf(stderr, "Modenum not implemented: %d\n", game_mode);
        return EXIT_FAILURE;
    }
	
    key = 0;    /* initialize key bitfield here for now */
    quit = false;

    /* initialize OpenGL for X11 */
    glxinit(XRES, YRES);

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
    default:
        break;
    }

    /* main loop */
    while (!quit) {
        /* begin processing events */
        if (XPending(dpy))
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
		default:
			fprintf(stderr, "Unknown game mode: %d\n", game_mode);
			quit = true;
			break;
		}

		glXSwapBuffers(dpy, window);
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
    if (__argc < 2) {
        fprintf(stderr, "Format: %s <modenum>\n", __argv[0]);
        return EXIT_FAILURE;
    }
    if (strlen(__argv[1]) > 1 || !isdigit((int)__argv[1][0])) {
        fprintf(stderr, "Malformed modenum: %s\n", __argv[1]);
        return EXIT_FAILURE;
    }

    game_mode = atoi(__argv[1]);

    if (game_mode < GM_DIAMONDS || game_mode > GM_SANDBOX) {
        fprintf(stderr, "Modenum not implemented: %d\n", game_mode);
        return EXIT_FAILURE;
    }

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
    default:
        break;
    }

    /* close OpenGL for WinAPI */
    wglfree(hInstance);

    return EXIT_SUCCESS;
}
#endif  /* _WIN32 */

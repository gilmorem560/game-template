/*
 * main - entry point
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	
	game_mode = atoi(argv[1]);
	
    key = 0;    /* initialize key bitfield here for now */
    quit = false;

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
    default:
        break;
    }

    /* main loop */
    while (!quit) {
        /* begin processing events */
        if (XPending(dpy))
            glxevent(dpy);

		switch(game_mode) {
		case GM_DIAMONDS:
			/* process next frame */
			diamond_renderframe();
			/* process movement */
			diamond_move();
			break;
		case GM_MAP:
			/* process next frame */
			map_renderframe();
			/* process movement */
			map_move();
			break;
		case GM_SANDBOX:
			/* process next frame */
			sandbox_renderframe();
			/* process movement */
			sandbox_move();
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
    key = 0;    /* initialize key bitfield here for now */
    quit = false;

    /* initialize OpenGL for WinAPI */
    wglinit(hInstance, nShowCmd, wndproc);

    /* prepare OpenGL assets */
    switch (game_mode) {
    case GM_DIAMONDS:
        diamond_init();
        break;
    default:
        break;
    }

    /* main loop */
    while (!quit) {
	/* TODO: Implement game modes */
        /* render next frame */
        if (!diamond_renderframe()) {
            fprintf(stderr, "renderframe: failure\n");
        } else {
            SwapBuffers(dc);
        }

        /* begin processing events */
        wglevent(wnd);

        /* process movement */
        diamond_move();

        /* prepare for next frame */
        if (diamond_angle == 360)
            diamond_angle = 0;
    }

    /* unload OpenGL assets */
    switch(game_mode) {
    case GM_DIAMONDS:
        diamond_free();
        break;
    default:
        break;
    }

    /* close OpenGL for WinAPI */
    wglfree(hInstance);

    return EXIT_SUCCESS;
}
#endif  /* _WIN32 */

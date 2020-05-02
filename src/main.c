/*
 * main - entry point
 */
#ifndef _WIN32
#include "../config.h"
#endif  /* _WIN32 */

/* game modes */
#include "modes/modes.h"

#define INITIAL_GM	GM_ACTOR_TEST

typedef enum {
	CONTEXT_OPENGL
} gfx_context;

const mode game_modes[MODE_COUNT] = {
	{logos_init, logos_render, logos_input, logos_routine, logos_free}
	,{titlescreen_init, titlescreen_render, titlescreen_input, titlescreen_routine, titlescreen_free}
	,{actor_test_init, actor_test_render, actor_test_input, actor_test_routine, actor_test_free}
};

/* I feel like this is irresponsible but whatever... */
#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
#else
/*
 * WinMain - windows entry point
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#endif  /* _WIN32 */
	gfx_context current_context = CONTEXT_OPENGL;
	isfullscreen = true;
    quit = false;
	
	#ifndef NDEBUG
	/* debugging can choose games 1-9 on command line */
    if (argc > 1) {
		if (strlen(argv[1]) > 1 || !isdigit((int) argv[1][0])) {
			fprintf(stderr, "Malformed modenum: %s\n", argv[1]);
			return EXIT_FAILURE;
		}
		mode_index = atoi(argv[1]);
    } else
	#endif /* NDEBUG */
	mode_index = INITIAL_GM;
	mode_index_prev = INITIAL_GM;
	
	/* TODO: Create an input state object */
	key_pressed = 0;    /* initialize key bitfield here for now */
    key_held = 0;
    mouse_moved_x = false;
	mouse_moved_y = false;

	/* start in debug mode */
	debug_init;

    /* initialize context for X11 */
	switch (current_context) {
	case CONTEXT_OPENGL:
		#ifndef _WIN32
		glxinit();
		#else
		wglinit(hInstance, nShowCmd, wndproc);
		#endif /* _WIN32 */
		break;
	default:
		fprintf(stderr, "init: unsupported graphics context %d\n", current_context);
		return EXIT_FAILURE;
	}

    /* prepare mode assets */
    game_modes[mode_index].init();

    /* main loop */
    while (!quit) {
		/* what were we last */
		mode_index_prev = mode_index;
		
		#ifndef _WIN32
        /* begin processing events */
		glxevent(dpy);
		#else
		wglevent(wnd);
		#endif /* _WIN32 */
		
		debug_pollkeys(key_held);
		
		/* process movement */
		game_modes[mode_index].input();
		
		/* run mode routine */
		game_modes[mode_index].routine();
		
		/* routine may change mode */
		if (mode_index == mode_index_prev)
			/* process next frame */
			game_modes[mode_index].render();
		else {
			game_modes[mode_index_prev].free();
			game_modes[mode_index].init();
		}
    }

    /* unload mode assets */
    game_modes[mode_index].free();

    /* close context for X11 */
	switch (current_context) {
	case CONTEXT_OPENGL:
		#ifndef _WIN32
		glxfree();
		#else
		wglfree(hInstance);
		#endif /* _WIN32 */
		break;
	default:
		fprintf(stderr, "free: unsupported graphics context %d\n", current_context);
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

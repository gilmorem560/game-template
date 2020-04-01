/*
 * stage - a single 3D playfield
 */
#include "stage.h"

/*
 * stage_init - OpenGL init
 */
bool stage_init(void)
{
	#ifndef NDEBUG
	printf("stage: init\n");
	#endif /* NDEBUG */
	
	/* enable GL states */
	glEnable(GL_DEPTH_TEST);	/* operating in 3D space */
	glEnable(GL_CULL_FACE);
	
	/* set background color */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	/* black background */
	
	/* back surface culling */
	glCullFace(GL_BACK);
	
	/* setup projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	return true;
}

/*
 * stage_render - OpenGL rendering
 */
bool stage_render(void)
{
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
	
	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/* flush */
	glFlush();

	/* display */
	#ifdef WIN32
		SwapBuffers(dc);
	#else
		glXSwapBuffers(dpy, window);
	#endif /* WIN32 */
	
	return true;
}

/*
 * stage_input - handle movement
 */
bool stage_input(void)
{
	/* actions */
	/* q - quit */	if (key & KEY_Q) quit = true;
	
	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (ISNUM(key) && !(key & KEY_4)) {
		stage_free();
		switch (key) {
			case KEY_1:
				diamond_init();
				game_mode = GM_DIAMONDS;
				break;
			case KEY_2:
				map_init();
				game_mode = GM_MAP;
				break;
			case KEY_3:
				sandbox_init();
				game_mode = GM_SANDBOX;
				break;
			default:
				quit = true;
				break;
		}
	}
	#endif /* NDEBUG */
	
	return true;
}

/*
 * stage_routine -  process object routine 
 */
bool stage_routine(void)
{
	return true;
}

/*
 * stage_free - OpenGL free
 */
bool stage_free(void)
{
	#ifndef NDEBUG
	printf("stage: free\n");
	#endif /* NDEBUG */
	
	return true;
}

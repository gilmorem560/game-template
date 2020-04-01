/*
 * diamond - display some diamonds
 */ 
#include "diamond.h"

/*
 * diamond_init - OpenGL init
 */
bool diamond_init(void)
{
	#ifndef NDEBUG
	printf("diamond: init\n");
	#endif /* NDEBUG */
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_FOG);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glCullFace(GL_BACK);
	
	diamond1 = glGenLists(1);
	glNewList(diamond1, GL_COMPILE);
	octahedron(0.5, 0.5, 0.5);
	glEndList();

	diamond2 = glGenLists(1);
	glNewList(diamond2, GL_COMPILE);
	octahedron(0.5, 0.5, 0.5);
	glEndList();

	diamond3 = glGenLists(1);
	glNewList(diamond3, GL_COMPILE);
	octahedron(0.5, 0.5, 0.5);
	glEndList();

	diamond4 = glGenLists(1);
	glNewList(diamond4, GL_COMPILE);
	octahedron(0.5, 0.5, 0.5);
	glEndList();

	diamond5 = glGenLists(1);
	glNewList(diamond5, GL_COMPILE);
	octahedron(0.5, 0.5, 0.5);
	glEndList();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	diamond_angle = 0;

	return true;
}

/*
 * diamond_render - OpenGL rendering cycle
 */
bool diamond_render(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glPushMatrix();
		glTranslated(0.5, 0.5, 0.0);
		glRotated(diamond_angle, 0.0, 1.0, 0.0);
		glCallList(diamond1);
    glPopMatrix();

    glPushMatrix();
		glTranslated(0.5, -0.5, 0.0);
		glRotated(diamond_angle, 0.0, 1.0, 0.0);
		glCallList(diamond2);
    glPopMatrix();

    glPushMatrix();
		glTranslated(-0.5, 0.5, 0.0);
		glRotated(diamond_angle, 0.0, -1.0, 0.0);
		glCallList(diamond3);
    glPopMatrix();

    glPushMatrix();
		glTranslated(-0.5, -0.5, 0.0);
		glRotated(diamond_angle, 0.0, -1.0, 0.0);
		glCallList(diamond4);
    glPopMatrix();

    glPushMatrix();
		glTranslated(0.0, 0.0, 0.0);
		glRotated(diamond_angle, 1.0, 0.0, 0.0);
		glCallList(diamond5);
    glPopMatrix();
	
	glFlush();

	#ifdef WIN32
		SwapBuffers(dc);
	#else
		glXSwapBuffers(dpy, window);
	#endif /* WIN32 */

    return true;
}

/*
 * diamond_input - handle movement based on key masks
 */
bool diamond_input(void)
{
	/* movement */
	/* r - rotate model */	if (key & KEY_R) diamond_angle++;

	/* actions */
    /* q - quit */			if (key & KEY_Q) quit = true;
	
	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (KEY_ISNUM(key) && !(key & KEY_1)) {
		diamond_free();
		switch (key) {
			case KEY_2:
				map_init();
				game_mode = GM_MAP;
				break;
			case KEY_3:
				sandbox_init();
				game_mode = GM_SANDBOX;
				break;
			case KEY_4:
				stage_init();
				game_mode = GM_STAGE;
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
 * diamond_routine - process diamond routine
 */
bool diamond_routine(void)
{
	/* constraints */
		/* angle */
		diamond_angle %= 360;

	return true;
}

/*
 * diamond_free - free OpenGL assets
 */
bool diamond_free(void)
{
	#ifndef NDEBUG
	printf("diamond: free\n");
	#endif /* NDEBUG */
	
    glDeleteLists(diamond1, 1);
    glDeleteLists(diamond2, 1);
    glDeleteLists(diamond3, 1);
    glDeleteLists(diamond4, 1);
    glDeleteLists(diamond5, 1);

    return true;
}

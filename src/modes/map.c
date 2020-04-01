/*
 * map - display a map with marker
 */ 
#include "map.h"

/*
 * map_init - OpenGL init
 */
bool map_init(void)
{
	#ifndef NDEBUG
	printf("map: init\n");
	#endif /* NDEBUG */
	
	/* enable GL features */
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
	
	/* prepare display lists */
	actor = glGenLists(1);
	glNewList(actor, GL_COMPILE);
	tetrahedron(1.0);
	glEndList();
	
	/* prepare properties */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

	/* prepare object properties */
	actor_x = 0.0;
	actor_y = 0.0;
	actor_z = 5.0;
	actor_angle = 0.0;
	
	return true;
}

/*
 * map_render - OpenGL rendering cycle
 */
bool map_render(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    /* render display lists and apply transformations */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glPushMatrix();
		glTranslated(actor_x, actor_y, -actor_z);
		glRotated(actor_angle, 0.0, 1.0, 0.0);
		glCallList(actor);
    glPopMatrix();
	
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
 * map_input - handle movement based on key masks
 */
bool map_input(void)
{
	/* movement */
    /* w - up */		if (key & KEY_W) actor_y += 0.01;
    /* s - down */		if (key & KEY_S) actor_y -= 0.01;
    /* a - left */		if (key & KEY_A) actor_x -= 0.01;
    /* d - right */		if (key & KEY_D) actor_x += 0.01;  
    /* z - zoom in */	if (key & KEY_Z) actor_z -= 0.1;  
    /* x - zoom out */	if (key & KEY_X) actor_z += 0.1;
    
	/* actions */
    /* q - quit */		if (key & KEY_Q) quit = true;
	
	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (ISNUM(key) && !(key & KEY_2)) {
		map_free();
		switch (key) {
			case KEY_1:
				diamond_init();
				game_mode = GM_DIAMONDS;
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
 * map_routine - process mode behavior
 */
bool map_routine(void)
{
	/* constraints */
		/* angle */
		actor_angle = fmod(++actor_angle, 360);

		/* edges */
		if (actor_y > 1.0) actor_y = 1.0;
		if (actor_y < -1.0) actor_y = -1.0;

		if (actor_x > 1.0) actor_x = 1.0;
		if (actor_x < -1.0) actor_x = -1.0;

		/* zoom */
		if (actor_z < 3.0) actor_z = 3.0;
		if (actor_z > 7.0) actor_z = 7.0;

	return true;
}

/*
 * map_free - free OpenGL assets
 */
bool map_free(void)
{
	#ifndef NDEBUG
	printf("map: free\n");
	#endif /* NDEBUG */
	
    /* free display lists */
    glDeleteLists(actor, 1);
	
    return true;
}

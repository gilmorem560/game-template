/*
 * sandbox - sandbox for testing
 */
#include "sandbox.h"

/* local assets */
static GLdouble verticies[] = {  0.5,  0.5,  0.5
							   , 0.5,  0.5, -0.5
							   , 0.5, -0.5,  0.5
							   , 0.5, -0.5, -0.5
							   ,-0.5,  0.5,  0.5
							   ,-0.5,  0.5, -0.5
							   ,-0.5, -0.5,  0.5
							   ,-0.5, -0.5, -0.5 };
						
static GLdouble colors[] = { 1.0, 0.0, 0.0
							,0.0, 1.0, 0.0
							,0.0, 0.0, 1.0
							,1.0, 1.0, 0.0
							,1.0, 0.0, 1.0
							,0.0, 1.0, 1.0
							,0.0, 0.0, 0.0
							,1.0, 1.0, 1.0 };

static GLdouble normals[] = {  1.0,  1.0,  1.0
							 , 1.0,  1.0, -1.0
							 , 1.0, -1.0,  1.0
							 , 1.0, -1.0, -1.0
							 ,-1.0,  1.0,  1.0
							 ,-1.0,  1.0, -1.0
							 ,-1.0, -1.0,  1.0
							 ,-1.0, -1.0, -1.0};
							 
static GLdouble texture_coords[] = {  0.0, 1.0
									 ,1.0, 1.0
									 ,0.0, 0.0
									 ,1.0, 0.0
									 ,0.0, 1.0
									 ,1.0, 1.0
									 ,0.0, 0.0
									 ,1.0, 0.0};
							
static GLubyte indicies[] = { 1, 0, 2, 3
							 ,0, 4, 6, 2
							 ,4, 5, 7, 6
							 ,5, 1, 3, 7
							 ,1, 5, 4, 0
							 ,2, 6, 7, 3 };
							 
static GLfloat light_pos[] = { 3.0f, 3.0f, 3.0f, 0.0f };
static GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
static GLfloat fog_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
static GLubyte texture_image[] = { 0 ,255 ,0   ,255
								  ,0 ,0   ,255 ,255
								  ,0 ,255 ,0   ,255
								  ,0 ,0   ,255 ,255 };
static GLint sandbox_texture;

/*
 * sandbox_init - OpenGL init
 */
bool sandbox_init(void)
{	
	#ifndef NDEBUG
	printf("sandbox: init\n");
	#endif /* NDEBUG */
	
	/* enable GL features */
	glEnable(GL_DEPTH_TEST);		/* operating in 3 dimensions */
	glEnable(GL_CULL_FACE);			/* allow culling for performance boost */
	glEnable(GL_TEXTURE_2D);		/* enable texturing */
	glEnable(GL_LIGHTING);			/* apply lighting */
	glEnable(GL_LIGHT0);			/* use first light */
	glEnable(GL_COLOR_MATERIAL);	/* allow vertex color in lighting */
	glEnable(GL_FOG);				/* fog calculations */
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* fog background */
	glClearColor(fog_color[0], fog_color[1], fog_color[2], fog_color[3]);
	glShadeModel(GL_SMOOTH);
	
	/* culling */
	glCullFace(GL_BACK);
	
	/* lighting setup */
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	
	/* material setup */
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	/* fog setup */
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 13.0f);
	
	/* projection setup */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 13.0);
	
	/* texture setup */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glGenTextures(1, &sandbox_texture);
	glBindTexture(GL_TEXTURE_2D, sandbox_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image);
		
	/* prepare arrays */
	glNormalPointer(GL_DOUBLE, 0, normals);
	glVertexPointer(3, GL_DOUBLE, 0, verticies);
	glColorPointer(3, GL_DOUBLE, 0, colors);
	glTexCoordPointer(2, GL_DOUBLE, 0, texture_coords);
	
	/* initialize properties */
	sandbox_angle_x = 0.0;
	sandbox_angle_y = 0.0;
	sandbox_shading_smooth = true;
	sandbox_zoom = -7.0;
	sandbox_mid_z = 0.0;
	sandbox_mid_pos = true;
	
	return true;
}

/*
 * sandbox_render - OpenGL rendering cycle
 */
bool sandbox_render(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
	
	/* render objects */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, sandbox_zoom);
	glRotated(sandbox_angle_x, 1.0, 0.0, 0.0);
	glRotated(sandbox_angle_y, 0.0, 1.0, 0.0);

	/* draw square of cubes */
	glPushMatrix();
		glTranslated(-1.5, -1.5, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(0.0, 1.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(0.0, 1.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(0.0, 1.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(-1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(-1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(-1.0, 0.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(0.0, -1.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
		glTranslated(0.0, -1.0, 0.0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
	glPopMatrix();

	/* draw inner moving cube */
	glPushMatrix();
		glTranslated(0.0, 0.0, sandbox_mid_z);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
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
 * sandbox_input - handle input
 */
bool sandbox_input(void)
{
	/* movement */
	/* w - spin up */			if (key & KEY_W) sandbox_angle_x -= 1.0;
	/* s - spin down */			if (key & KEY_S) sandbox_angle_x += 1.0;
	/* a - spin left */			if (key & KEY_A) sandbox_angle_y -= 1.0;
	/* d - spin right */		if (key & KEY_D) sandbox_angle_y += 1.0;
	/* z - zoom in */			if (key & KEY_Z) sandbox_zoom += 0.1;
	/* x - zoom out */			if (key & KEY_X) sandbox_zoom -= 0.1;
	
	#ifndef NDEBUG
	/* r - windowed */		if (key & KEY_R) { setwindowed(640, 480); key &= ~KEY_R; }
	/* f - fullscreen */	if (key & KEY_F) { setfullscreen(); key &= ~KEY_F; }
	/* q - quit */				if (key & KEY_Q) quit = true;
	/* v - uncapture mouse */	if (key & KEY_V) { mouse_captured = false; debug_cursor_changed = true; }
	/* c - uncapture mouse */	if (key & KEY_C) { mouse_captured = true;  debug_cursor_changed = true; }
	/* hot mode switching for debugging */
	if (KEY_ISNUM(key) && !(key & KEY_3)) {
		sandbox_free();
		switch (key) {
			case KEY_1:
				diamond_init();
				game_mode = GM_DIAMONDS;
				break;
			case KEY_2:
				map_init();
				game_mode = GM_MAP;
				break;
			case KEY_4:
				stage_init();
				game_mode = GM_STAGE;
				break;
			case KEY_5:
				scene_test_init();
				game_mode = GM_SCENE_TEST;
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
 * sandbox_routine - main routine
 */
bool sandbox_routine(void)
{
	/* constraints */
		/* angle */
		sandbox_angle_x = fmod(sandbox_angle_x, 360);
		sandbox_angle_y = fmod(sandbox_angle_y, 360);

		/* zoom */
		if (sandbox_zoom > -3.82) sandbox_zoom = -3.82;
		if (sandbox_zoom < -10.18) sandbox_zoom = -10.18;

		/* middle cube movement */
		if (sandbox_mid_pos) {
			if (sandbox_mid_z <= 2.0) sandbox_mid_z += 0.1;
			else sandbox_mid_pos = false;
		} else {
			if (sandbox_mid_z >= -2.0) sandbox_mid_z -= 0.1;
			else sandbox_mid_pos = true;
		}

	return true;
}

/*
 * sandbox_free - free OpenGL assets
 */
bool sandbox_free(void)
{
	#ifndef NDEBUG
	printf("sandbox: free\n");
	#endif /* NDEBUG */
	
	glDeleteTextures(1, &sandbox_texture);
	
	return true;
}

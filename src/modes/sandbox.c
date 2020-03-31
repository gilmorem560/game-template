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
static GLint texture;

/*
 * sandbox_init - OpenGL init
 */
bool sandbox_init(void)
{	
	#ifndef NDEBUG
	fprintf(stdout, "sandbox: init\n");
	#endif /* NDEBUG */
	
	/* Enable GL features */
	glEnable(GL_DEPTH_TEST);		/* operating in 3 dimensions */
	glEnable(GL_CULL_FACE);			/* allow culling for performance boost */
	glEnable(GL_LIGHTING);			/* apply lighting */
	glEnable(GL_LIGHT0);			/* use first light */
	glEnable(GL_COLOR_MATERIAL);	/* allow vertex color in lighting */
	glEnable(GL_FOG);				/* fog calculations */
	glEnable(GL_TEXTURE_2D);		/* enable texturing */
	glEnableClientState(GL_NORMAL_ARRAY);	/* Enable vertex, color, and normal arrays for performance boost */
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* Prepare propeties */
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
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
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image);
		
	/* Prepare arrays */
	glNormalPointer(GL_DOUBLE, 0, normals);
	glVertexPointer(3, GL_DOUBLE, 0, verticies);
	glColorPointer(3, GL_DOUBLE, 0, colors);
	glTexCoordPointer(2, GL_DOUBLE, 0, texture_coords);
	
	/* initialize properties */
	angleX = 0.0;
	angleY = 0.0;
	smoothShading = true;
	flatShading = false;
	zoom = -7.0;
	z_dist = 0.0;
	z_pos = true;
	
	return true;
}

/*
 * sandbox_renderframe - OpenGL rendering cycle
 */
bool sandbox_renderframe(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
	
	if (smoothShading)
		glShadeModel(GL_SMOOTH);
	
	if (flatShading)
		glShadeModel(GL_FLAT);
	
	/* Render objects */

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, zoom);
	glRotated(angleX, 1.0, 0.0, 0.0);
	glRotated(angleY, 0.0, 1.0, 0.0);
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
	glPushMatrix();
		glTranslated(0.0, 0.0, z_dist);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicies);
	glPopMatrix();
	
	/* Flush */
	glFlush();
	
	return true;
}

/*
 * sandbox_move - handle movement
 */
bool sandbox_move(void)
{
	/* w - spin up */
	if (key & KEY_W)
		angleX -= 1.0;
		
	/* s - spin down */
	if (key & KEY_S)
		angleX += 1.0;
		
	/* a - spin left */
	if (key & KEY_A)
		angleY -= 1.0;
		
	/* d - spin right */
	if (key & KEY_D)
		angleY += 1.0;
	
	/* f - flat shading */
	if (key & KEY_F) {
		smoothShading = false;
		flatShading = true;
	}
	
	/* g - smooth shading */
	if (key & KEY_G) {
		smoothShading = true;
		flatShading = false;
	}
	
	/* z - zoom in */
	if (key & KEY_Z)
		zoom += 0.1;
	
	/* x - zoom out */
	if (key & KEY_X)
		zoom -= 0.1;
	
	/* q - quit */
	if (key & KEY_Q)
		quit = true;
	
	/* limits */
	if (angleX > 360.0)
		angleX = 0.0;
	else if (angleX < 0.0)
		angleX = 360.0;
	
	if (angleY > 360.0)
		angleY = 0.0;
	else if (angleY < 0.0)
		angleY = 360.0;
	
	if (zoom > -3.82)
		zoom = -3.82;
	
	if (zoom < -10.18)
		zoom = -10.18;
	
	if (z_pos)
	{
		if (z_dist <= 2.0)
			z_dist += 0.1;
		else
			z_pos = false;
	} else {
		if (z_dist >= -2.0)
			z_dist -= 0.1;
		else
			z_pos = true;
	}	
	
	return true;
}

/*
 * sandbox_free - Free OpenGL assets
 */
bool sandbox_free(void)
{
	#ifndef NDEBUG
	fprintf(stdout, "sandbox: free\n");
	#endif /* NDEBUG */
	
	glDeleteTextures(1, &texture);
	
	return true;
}

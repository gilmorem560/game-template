/*
 * sandbox - sandbox for testing
 */
#include "sandbox.h"

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
							
static GLubyte indicies[] = { 1, 0, 2, 3
							 ,0, 4, 6, 2
							 ,4, 5, 7, 6
							 ,5, 1, 3, 7
							 ,1, 5, 4, 0
							 ,2, 6, 7, 3 };
							 
static bool smoothShading;
static bool flatShading;
static double zoom;
static double z_dist;
static bool z_pos;

/*
 * sandbox_init - OpenGL init
 */
bool sandbox_init(void)
{
	#ifndef NDEBUG
	fprintf(stdout, "sandbox: init\n");
	#endif /* NDEBUG */
	
	/* Enable GL features */
	glEnable(GL_DEPTH_TEST);	/* operating in 3 dimensions */
	glEnable(GL_CULL_FACE);		/* allow culling for performance boost */
	glCullFace(GL_BACK);		/* only looking from outside in */
	
	//glEnableClientState(GL_NORMAL_ARRAY);	/* Enable vertex, color, and normal arrays for performance boost */
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	/* Prepare arrays */
	glVertexPointer(3, GL_DOUBLE, 0, verticies);
	glColorPointer(3, GL_DOUBLE, 0, colors);
	
	/* Prepare textures */
	
	/* Prepare propeties */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 13.0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
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
	
	if (angleX > 360.0)
		angleX = 0.0;
	else if (angleX < 0.0)
		angleX = 360.0;
	
	if (angleY > 360.0)
		angleY = 0.0;
	else if (angleY < 0.0)
		angleY = 360.0;
	
	if (zoom > -5.0)
		zoom = -5.0;
	
	if (zoom < -9.0)
		zoom = -9.0;
	
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
	
		
	/* q - quit */
	if (key & KEY_Q)
		quit = true;
	
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
	/* Free display lists */
	
	//glDeleteLists(cube, 1);
	
	return true;
}

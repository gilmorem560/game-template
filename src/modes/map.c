/*
 * map - Display a map with marker
 */ 
#include "map.h"

/*
 * map_init - OpenGL init
 */
bool map_init(void)
{
	#ifndef NDEBUG
	fprintf(stdout, "map: init\n");
	#endif /* NDEBUG */
	
	/* Enable GL features */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	/* Prepare display lists */
	actor = glGenLists(1);
	glNewList(actor, GL_COMPILE);
	tetrahedron(1.0);
	glEndList();
	
	/* Prepare properties */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	actor_x = 0.0;
	actor_y = 0.0;
	actor_z = 5.0;
	actor_angle = 0.0;
	return true;
}

/*
 * map_renderframe - OpenGL rendering cycle
 */
bool map_renderframe(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    /* Render display lists and apply transformations */
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
		glTranslated(actor_x, actor_y, -actor_z);
		glRotated(actor_angle, 0.0, 1.0, 0.0);
		glCallList(actor);
    glPopMatrix();
	
	/* Flush */
	glFlush();

    return true;
}

/*
 * map_move - handle movement based on key masks
 */
bool map_move(void)
{
	if (actor_angle++ == 360.0)
		actor_angle = 0.0;
	
    /* w - up */
    if ((key & KEY_W)
	&& (actor_y < 1.0))
	actor_y += 0.01;

    /* s - down */
    if ((key & KEY_S)
	&& (actor_y > -1.0))
	actor_y -= 0.01;

    /* a - left */
    if ((key & KEY_A)
	&& (actor_x > -1.0))
	actor_x -= 0.01;

    /* d - right */
    if ((key & KEY_D)
	&& (actor_x < 1.0))
	actor_x += 0.01;
    
    /* z - zoom in */
    if ((key & KEY_Z)
	&& (actor_z > 3.0))
	actor_z -= 0.1;
    
    /* x - zoom out */
    if ((key & KEY_X)
	&& (actor_z < 7.0))
	actor_z += 0.1;
    
    /* q - quit */
    if (key & KEY_Q)
	    quit = true;

    return true;
}

/*
 * map_free - Free OpenGL assets
 */
bool map_free(void)
{
	#ifndef NDEBUG
	fprintf(stdout, "map: free\n");
	#endif /* NDEBUG */
	
    /* Free display lists */
    glDeleteLists(actor, 1);
	
    return true;
}

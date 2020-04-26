/*
 * cube - a normaler than average cube
 */ 
#include "../actors.h"

/* at_cube - a normaler than average cube */
static GLdouble at_cube_vertex[24] = { 
	-1.0,  1.0, 1.0
	,-1.0, -1.0, 1.0
	, 1.0, -1.0, 1.0
	, 1.0,  1.0, 1.0
	, 1.0,  1.0, -1.0
	, 1.0, -1.0, -1.0
	,-1.0, -1.0, -1.0
	,-1.0,  1.0, -1.0 };
							 
static GLdouble at_cube_normal[24] = {
	-1.0,  1.0,  1.0
	,-1.0, -1.0,  1.0
	, 1.0, -1.0,  1.0
	, 1.0,  1.0,  1.0
	, 1.0,  1.0, -1.0
	, 1.0, -1.0, -1.0
	,-1.0, -1.0, -1.0
	,-1.0,  1.0, -1.0 };
							 
static GLdouble at_cube_color[24] = {
	1.0, 0.0, 0.0
	,0.0, 1.0, 0.0
	,0.0, 0.0, 1.0
	,1.0, 1.0, 0.0
	,0.0, 1.0, 1.0
	,1.0, 0.0, 1.0
	,1.0, 1.0, 0.5
	,0.5, 1.0, 1.0 };
							
static GLubyte at_cube_index[24] = {
	0, 1, 2, 3
	,3, 2, 5, 4
	,4, 5, 6, 7
	,7, 6, 1, 0
	,7, 0, 3, 4
	,1, 6, 5, 2 };

actor *at_cube_new(void)
{
	actor *new_actor = actor_new_actor(AT_CUBE, at_cube_render, at_cube_routine);
	
	return new_actor;
}

/* 00 - init */
void at_cube_init(actor *this)
{
	/* setup model */
	this->vertex_array = at_cube_vertex;
	this->normal_array = at_cube_normal;
	this->color_array = at_cube_color;
	this->vao_indicies = at_cube_index;
	
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_cube_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_cube_render - render the cube itself
 */
void at_cube_render(actor *this)
{
		/* bind actor arrays */
		glVertexPointer(3, GL_DOUBLE, 0, this->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, this->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, this->color_array);
		
		/* draw actor */
		glPushMatrix();
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, this->vao_indicies);
		glPopMatrix();
		
		return;
}

/*
 * at_cube_routine - handle routing to various routines
 */
void at_cube_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_cube_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_cube_free(this);
		break;
	default:
		fprintf(stderr, "Unknown routine for actor type %d: %d\n", this->type, this->routine_index);
		break;
	}
	
	return;
}

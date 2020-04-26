/*
 * cube - a normaler than average cube
 */ 
#include "../actors.h"

/* at_cube - a normaler than average cube */
static GLdouble at_tet_vertex[12] = { 
	0.0, -1.0, -1.0
	,1.0, -1.0, 1.0
	,-1.0, -1.0, 1.0
	,0.0, 1.0, 0.0 };
							 
static GLdouble at_tet_normal[12] = {
	0.0, -1.0, -1.0
	,1.0, -1.0, 1.0
	,-1.0, -1.0, 1.0
	,0.0, 1.0, 0.0 };
							 
static GLdouble at_tet_color[12] = {
	1.0, 0.0, 0.0
	,0.0, 1.0, 0.0
	,0.0, 0.0, 1.0
	,1.0, 1.0, 0.0 };
							
static GLubyte at_tet_index[12] = {
	0, 1, 2
	,0, 3, 1
	,0, 2, 3
	,3, 2, 1
};

actor *at_tet_new(void)
{
	actor *new_actor = actor_new_actor(AT_TETRAHEDRON, at_tet_render, at_tet_routine);
	
	return new_actor;
}

/* 00 - init */
void at_tet_init(actor *this)
{
	/* setup model */
	this->vertex_array = at_tet_vertex;
	this->normal_array = at_tet_normal;
	this->color_array = at_tet_color;
	this->vao_indicies = at_tet_index;
	
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_tet_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_tet_render - render the tetrahedron itself
 */
void at_tet_render(actor *this)
{
		/* bind actor arrays */
		glVertexPointer(3, GL_DOUBLE, 0, this->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, this->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, this->color_array);
		
		/* draw actor */
		glPushMatrix();
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, this->vao_indicies);
		glPopMatrix();
		
		return;
}

/*
 * at_tet_routine - handle routing to various routines
 */
void at_tet_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_tet_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_tet_free(this);
		break;
	default:
		fprintf(stderr, "Unknown routine for actor type %d: %d\n", this->type, this->routine_index);
		break;
	}
	
	return;
}

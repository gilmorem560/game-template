/*
 * triangle - a normaler than average triangle
 */ 
#include "../actors.h"

/* at_triangle - a normaler than average triangle */
static GLdouble at_triangle_vertex[9] = { 
	0.0, 1.0, 0.0
	,-1.0, -1.0, 0.0
	,1.0, -1.0, 0.0
};
							 
static GLdouble at_triangle_normal[9] = {
	0.0, 1.0, 0.0
	,-1.0, -1.0, 0.0
	,1.0, -1.0, 0.0
};
							 
static GLdouble at_triangle_color[9] = {
	1.0, 1.0, 0.0
	,1.0, 1.0, 0.0
	,1.0, 1.0, 0.0
};
							
static GLubyte at_triangle_index[3] = {
	0, 1, 2
};

actor *at_triangle_new(void)
{
	actor *new_actor = actor_new_actor(AT_TRIANGLE, at_triangle_render, at_triangle_routine);
	
	return new_actor;
}

/* 00 - init */
void at_triangle_init(actor *this)
{
	/* setup model */
	this->vertex_array = at_triangle_vertex;
	this->normal_array = at_triangle_normal;
	this->color_array = at_triangle_color;
	this->vao_indicies = at_triangle_index;
	
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_triangle_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_triangle_render - render the triangle itself
 */
void at_triangle_render(actor *this)
{
		/* bind actor arrays */
		glVertexPointer(3, GL_DOUBLE, 0, this->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, this->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, this->color_array);
		
		/* draw actor */
		glPushMatrix();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, this->vao_indicies);
		glPopMatrix();
		
		return;
}

/*
 * at_triangle_routine - handle routing to various routines
 */
void at_triangle_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_triangle_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_triangle_free(this);
		break;
	default:
		fprintf(stderr, "Unknown routine for actor type %d: %d\n", this->type, this->routine_index);
		break;
	}
	
	return;
}

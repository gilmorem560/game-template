/*
 * person - a person
 */ 
#include "../actors.h"

/* at_person - a person */
static GLdouble at_person_vertex[] = { 0.0 };					 
static GLdouble at_person_normal[] = { 0.0 };				 
static GLdouble at_person_color[] = { 0.0 };	
static GLubyte at_person_index[] = { 0 };

actor *at_person_new(void)
{
	actor *new_actor = actor_new_actor(AT_PERSON, at_person_render, at_person_routine);
	
	return new_actor;
}

/* 00 - init */
void at_person_init(actor *this)
{
	/* setup model */
	this->vertex_array = at_person_vertex;
	this->normal_array = at_person_normal;
	this->color_array = at_person_color;
	this->vao_indicies = at_person_index;
	
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_person_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_person.c_render - render the person.c itself
 */
void at_person_render(actor *this)
{
		/* bind actor arrays */
		glVertexPointer(3, GL_DOUBLE, 0, this->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, this->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, this->color_array);
		
		/* draw actor */
		glPushMatrix();
			glDrawElements(GL_QUADS, 1, GL_UNSIGNED_BYTE, this->vao_indicies);
		glPopMatrix();
		
		return;
}

/*
 * at_person.c_routine - handle routing to various routines
 */
void at_person_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_person_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_person_free(this);
		break;
	default:
		fprintf(stderr, "Unknown routine for actor type %d: %d\n", this->type, this->routine_index);
		break;
	}
	
	return;
}

/*
 * actor - an acting object in 3D space
 */
#include <stdlib.h>
#include "actor.h"

actor *actor_new_actor(signed int type, void (*render)(actor *this), void (*routine)(actor *this))
{
	actor *new_actor = malloc(sizeof (actor));
		new_actor->type = type;
		new_actor->routine_index = AR_NULL;
		new_actor->properties = NULL;
		new_actor->vertex_array = NULL;
		new_actor->normal_array = NULL;
		new_actor->color_array = NULL;
		new_actor->vao_indicies = NULL;
		new_actor->render = render;
		new_actor->routine = routine;
	
	return new_actor;
}

void actor_render(actor *this)
{
	this->render(this);
	
	return;
}

void actor_routine(actor *this, signed char routine_index)
{
	if (routine_index == AR_NULL)
		return;
	
	this->routine_index = routine_index;
	this->routine(this);
	
	return;
}

void actor_free(actor *this)
{
	free(this);
	
	return;
}

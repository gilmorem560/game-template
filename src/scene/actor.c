/*
 * actor - an acting object in 3D space
 */
#include <stdlib.h>
#include "actor.h"

/*
 * new_actor - provides a new actor with initialized variables
 */
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

/*
 * render - call the actor's render loop
 * 
 * 	calls to render should always call through this mechanism
 * 	rather than calling the function pointer directly
 */
void actor_render(actor *this)
{
	this->render(this);
	
	return;
}

/*
 * routine - run the actor's routine at index
 * 
 * 	AR_NULL, AR_INIT, and AR_FREE are globally defined
 * 	all other routines are defined on the actor level
 * 	a consuming construct must know the routine indicies
 * 	of the actors it is consuming
 * 
 * 	actors must implement AR_NULL, AR_INIT, and AR_FREE
 *  or expect the default routine to be called in their
 *  place
 */
void actor_routine(actor *this, signed char routine_index)
{
	if (routine_index == AR_NULL)
		return;
	
	this->routine_index = routine_index;
	this->routine(this);
	
	return;
}

/*
 * free - free the actor
 */
void actor_free(actor *this)
{
	free(this);
	
	return;
}

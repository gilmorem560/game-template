/*
 * actor - an acting object in 3D space
 */
#ifndef __ACTOR_H__
#define __ACTOR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* collision objects */
#include "../primitives/collision.h"

/*
 * an actor is a type object
 * an actor has a current:
 *  type - the type of actor, this is a property used by modes
 * 			actor itself does not define any types other than null
 *  routine_index - the routine value being run currently
 *  collision_data - collision info structure
 *  properties - properties of the object itself
 * 	GL arrays - arrays of data used for rendering in GL
 *  render - render function, performs based on other properties
 * 	routine - function that routes object routines
 * 		three routine values are defined
 * 		-1 - null
 * 		0 - init
 * 		1 - free
 * 		all others are implementation defined
 * 
 *  implementation:
 * 		enumerate/define mode's actor types
 * 		create actor related functionality
 * 			ensure defined routines above are provided
 * 		provide an actor routing method that calls routines
 * 			using switch on routine values
 * 		provide a rendering method that render's the actor model
 * 		routine methods will act on properties and collision data
 */
typedef struct actor {
	signed short type;
	signed char routine_index;
	collision collision_data;
	void *properties;
	double *vertex_array;
	double *normal_array;
	double *color_array;
	unsigned char *vao_indicies;
	void (*render)(struct actor *this);
	void (*routine)(struct actor *this);
} actor;
#define AT_NULL		-1

#define	AR_NULL	-1
#define	AR_INIT	0
#define	AR_FREE	1

actor *actor_new_actor(signed int type, void (*render)(actor *this), void (*routine)(actor *this));
void actor_render(actor *this);
void actor_routine(actor *this, signed char routine_index);
void actor_free(actor *this);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTOR_H__ */

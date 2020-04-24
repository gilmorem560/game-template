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
 *  an actor distinguishes itself from an environment
 * types are defined by modes
 * an actor has a current:
 *  type_router - do we call a generic type router
 * 	model - model being displayed, TODO: need to implement model abstraction
 *  routine - current routine
 *  collision_data - collision info structure
 *  properties - TODO: implement abstraction for actor properties
 * 		position
 * 		size
 * 	router - function that routes object routines
 * 		two routine values are defined
 * 		0 - init
 * 		1 - free
 * 		all others are implementation defined
 * 
 *  implementation:
 * 		enumerate/define mode's actor types
 * 		create object related functionality
 * 			ensure defined routines above are provided
 * 		provide an object routing method that calls routines
 * 			using switch on routine values
 * 		a router pointer is provided but mode may define
 * 			type-wide routers too
 * 			combinations of custom and type routers are allowed
 * 			precedence is implementation dependent
 * 		router methods will act on properties and collision data
 */
typedef struct actor {
	signed short type;
	bool type_router;
	// model
	signed char routine;
	collision collision_data;
	// properties
	void (*router)(void);
} actor;
#define ACTOR_ROUTINE_NULL	-1
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTOR_H__ */

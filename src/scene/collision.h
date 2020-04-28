/*
 * collision - basic collision routines and primitives
 */
#ifndef __COLLISION_H__
#define __COLLISION_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
#include <stdbool.h>

/* shape primitives for complex collision */
#include "../graphics/primitives/prim.h"

/* collision shape
 * 
 * shape types implemented by the engine
 *  the shape number is provided to a routing
 *  switch to determine which collision method is necessary
 */
typedef enum {
	COLLISION_BOUND_BOX
	//,COLLISION_SPHERE
} e_collision_shape;

/*
 * collision
 * 
 *  collision is either a shape or implementation-defined mesh collision
 */
typedef struct collision {
	bool mesh;
	e_collision_shape shape;
	double *dims;
	void *mesh_data;
} collision;

/*
 * collision_router - collision primitives should be few
 * 	method determination will be static and switch driven
 *  collision routing for mesh data is implemented by the object
 */
void collision_router(e_collision_shape shape_a, double *dim_a, e_collision_shape shape_b, double *dim_b);

/* TODO: Implement box primitive
 * all collision primitive to primitive relationships will be explicit
 *  if a relationship is not defined, collision between the object types
 * 	is likewise undefined
 */
void collide_box_box(double *dim_a, double *dim_b);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COLLISION_H__ */

/*
 * collision_index - a collision index entry and helper objects
 */
#ifndef __COLLISION_INDEX_H__
#define __COLLISION_INDEX_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
#include "../primitives/collision.h"
	
/* collision planning
 * ------------------
/* collision can be either defined as a geometric primitive or a mesh
 * the goal is to, using the least memory, store and index the
 *  information needed by an object to calculate what will happen to
 *  to itself upon collision with an object.
 * no individual object is going to calculate what happens to something
 *  that it has collided with, it only needs to know what it does after
 *  that collision
 * 
 * collision shape
 * 
 * shape types implemented by the engine
 *  the shape number is provided to a routing
 *  switch to determine which collision method is necessary
 * 
 * collision index table
 * 
 * the scene graph will contain a collision index table
 * entries will contain the scene ID of the object
 * 	the type of the object
 * 	whether the collision is a mesh or not
 *  a shape enumeration, with a growing list of geometric primitives
 *  a pointer to a list of dimensions (defined by shape implementations)
 * 
 * collision state
 * 
 * the collision state object is populated with any collisions that have
 * 	occurred in the past cycle, that way we don't recalc a collision
 *  we already calculated. the state will indicate which objects collided
 *  
 */



/*
 * collision_index - table of object metadata
 * 	object_id - object ID in graph
 *  object_type - object type
 *  mesh - is this a collision mesh, if not is bounding geometry
 *  shape - pointer to list of dimensions
 * 		shape dimensions must be defined by shapes themselves
 * 		functions operating on a shape must know the number of dimensions
 * 		used, shape can be vague, but shape-based collision must
 * 		reduce to common dimensions
 *  mesh_data - implementation defined data structure, if a shape
 * 		uses a mesh the receiving function must know what kind
 * 		of data it interprets. if common functions are desired
 * 		mesh data must be formatted or a wrapper providing 
 * 		necessary meta-data implemented
 */
typedef struct {
	int object_id;
	int object_type;
	collision *collision_data;
} collision_index;

/* TODO: Collision index allocation and adjustment methods */

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COLLISION_INDEX_H__ */

 /*
  * scene - a primitive scene graph
  */
#ifndef __SCENE_H__
#define __SCENE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* include GL for types */
#include "../contexts/glcontext.h"
/* actors */
#include "actor.h"
/* collision detection */
#include "collision_index.h"
	
typedef enum {
	PROJECTION_ORTHAGONAL
	,PROJECTION_FRUSTUM
} projection_type;

typedef struct {
	signed short id;
	actor *actor_obj;
} scene_actor;
#define SCENE_ACTOR_NULL	-1

/*
 * node in a scene graph
 * a node has geometry TODO: implement model abstraction
 * a node has children and a count on those children
 * environment is a special secondary node in the scene that also has children, the scene is the parent node of these two
 * 
 */
typedef struct node {
	scene_actor actor;
	GLdouble *vertex_array;
	GLdouble *normal_array;
	GLdouble *color_array;
	GLubyte *vao_indicies;
	struct node *children;
	unsigned int children_count;
	/* the node will be responsible for maintaining and cleaning its children records */
	/*	note: a scene does not require a collision table
	*  	this may be null if the scene does not implement
	* 		any objects employing collision
	* 		behavior of objects with collision in scenes
	* 		with no index is undefined
	*/
} node;
typedef node environment;
	
/* scene graph
 *	 contains the collection of actors in the scene, as well as the nodes that connect them
 *   actors can become orphaned, garbage handling is necessary
 * 
 *  the collision table is populated with collision information about the scene
 *  actors are responsible for inserting and removing themselves from the index
 *   the index can provide optimization functionality, actors will just perform requests for new data
 *   and freeing of old data
 */
typedef struct scene {
	GLdouble *prj;
	projection_type prj_type;
	node *root_node;
	environment *root_environment;
	actor *camera;
	node *nodes;
	int node_count;
	collision_index *collision_table;
} scene;

void scene_projection_new(scene *graph, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SCENE_H__ */

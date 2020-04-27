/*
 * scene - a primitive scene graph
 * 
 * common variables:
 * 
 * graph -> the scene graph being manipulated
 * signed short node_id = the ID of a node in the graph being manipulated
 * 
 * node state manipulation in the scene collection should always occur via
 * methods here, these methods aim to standardize different handling
 * of node status without introducing some complex system of flags
 * and variables for the consuming code to set, in the collection,
 * a status is just that, a state of the object
 * 
 * some node states can be changed on the lower level if desired
 * or if debugging but this is discouraged, especially modifications
 * that disrupt the index of any collections or delete memory
 * 
 * eventually an error handler will be written for any invalid memory
 * access, hopefully to catch improperly handled nodes
 */
#ifndef __SCENE_H__
#define __SCENE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* nodes */
#include "node.h"
/* collision detection */
#include "collision_index.h"
	
typedef enum {
	PROJECTION_ORTHAGONAL
	,PROJECTION_FRUSTUM
} projection_type;
	
/* scene graph
 *	the scene graph represents the scene as a whole and consists of:
 * 
 *  the projection applied to display the scene
 *  TODO: miscellaneous display settings
 * 
 *  the bounding box of the scene, a bounding box is optional and only necessary
 *  if objects must interact with one
 * 
 *  a scene is ultimately a collection of nodes and those nodes' relationships
 *  to one another
 * 
 *  a scene is designed in such a way that its nodes can be traversed,
 *  routines performed, data routed, and rendering presented in a relatively
 *  standard pipeline
 * 
 *  parent-child relationships between nodes are managed by the nodes themselves
 *  the graph provides facilities for child node collection maintenance as
 *  a subset of node collection maintenance, but all other behaviors must be
 *  handled by nodes themselves when they register their children in the scene
 * 
 *  a scene has a few special, but optional, node pointers provided
 *  utilizing these nodes allows for the use of baked in node collision and
 *  node manipulation functionality but is not necessary to scene construction
 */
typedef struct {
	double prj[6];
	projection_type prj_type;
	
	double bounding_box[6];
	collision_index *collision_table;
	
	node **nodes;
	int node_count;
	
	node *root_node;
	node *camera;
	node *environment;
	node *player;
} scene;

/* ==================== Scene Display Settings ==================== */
void scene_projection_new(scene *graph, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane);

/* ==================== Node Collection Management ==================== */

/* primary collection management */
signed short scene_addnode(scene *graph, signed short type, void (*render)(node *), void (*routine)(node *));
void scene_switchactivenode(scene *graph, signed short node_id);
void scene_revivenode(scene *graph, signed short node_id);

/* child collection management */
void scene_setchildnode(scene *graph, signed int parent, signed int child);

/* ==================== Node Collision ==================== */

bool scene_enforceboundingnode(scene *graph, signed short node_id);

/* ==================== Node Manipulation ==================== */

void scene_positionnode(scene *graph, signed short node_id, point3d position);
void scene_rotatenode(scene *graph, signed short node_id, point3d angle);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SCENE_H__ */

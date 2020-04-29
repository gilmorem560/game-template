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

#include <math.h>
#define sabs(a) (unsigned short) fabs((double) a)
	
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
 * 
 *  a scene can be used in conjunction with other rendering, for instance
 *  if a scene is first projected, it can then be drawn on top of orthagonally
 *  for items such as HUD elements, special effects, maybe even...sh...
 *  .
 *  .sha..shaders
 *  .
 *  but also, an orthagonal plane will also be behind the stage such that any
 *  fully transparent fragments will display the background plane
 *  the scene does not care about this stuff and is only as constrained to it
 *  as the consuming construct decides it must be
 */
typedef struct scene {
	double prj[6];
	projection_type prj_type;
	
	double bounding_box[6];
	
	node **nodes;
	unsigned short node_count;
	
	node *root_node;
	node *camera;
	node *environment;
	node *player;
} scene;

/* ==================== Scene Creation and Destruction ==================== */
scene *scene_new(void);
void scene_free(scene *this);

/* ==================== Scene Display Settings ==================== */
void scene_projection_new(scene *this, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane);

/* ==================== Node Collection Management ==================== */
/* primary collection management */
unsigned short scene_addnode(scene *this, signed short type, void (*render)(node *), void (*routine)(node *));
void scene_switchactivenode(scene *this, signed short node_id);

/* child collection management */
int scene_setchildnode(scene *this, signed short parent_node, signed short child_node);

/* ==================== Bounding Box ==================== */
void scene_enforcebounding(scene *this);

/* ==================== Node Manipulation ==================== */
void scene_positionnode(scene *this, signed short node_id, point3d position);
void scene_rotatenode(scene *this, signed short node_id, point3d angle);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SCENE_H__ */

/*
 * node - a single node in the scene graph
 */
#ifndef __NODE_H__
#define __NODE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* actors */
#include "actor.h"

/*
 * node in a scene graph
 * a node has an actor which consists of geometry and animation, collision, and management routines
 * a node has children and a count on those children
 * a node must manage its children
 * a node must clean up another node's child collection if it takes control of a child
 */
typedef struct node {
	signed short id;
	signed char type;
	signed short routine_index;
	actor *node_actor;
	point3d position;
	point3d rotation;
	void *properties;
	struct node **children;
	unsigned int children_count;
	void (*render)(struct node *this);
	void (*routine)(struct node *this);
	/* the node will be responsible for maintaining and cleaning its children records */
	/*	note: a scene does not require a collision table
	*  	this may be null if the scene does not implement
	* 		any objects employing collision
	* 		behavior of objects with collision in scenes
	* 		with no index is undefined
	*/
} node;
#define NID_DELETED	0

#define NT_NULL		-1

#define NR_NULL		-1
#define	NR_INIT		0
#define	NR_FREE		1

node *node_new(signed short id, signed int type, void (*render)(node *this), void (*routine)(node *this));
void node_render(node *this);
void node_routine(node *this, signed char routine_index);
void node_free(node *this);
unsigned short node_addchildnode(node *this, node *child);
void node_prunechildnode(node *this, unsigned int index);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif /* __NODE_H__ */

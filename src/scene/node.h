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
 * structure to indicate the collision(s) with an object
 *  sign bit indicates side
 *  store index in remaining space
 */
typedef struct collided {
	unsigned short id;
	signed char x;
	signed char y;
	signed char z;
} collided;

/*
 * node in a scene graph
 * a node has an actor which consists of geometry and animation, collision, and management routines
 * a node has children and a count on those children
 * a node must manage its children
 * a node must clean up another node's child collection if it takes control of a child
 * a node may be bound by the world
 */
typedef struct node {
	signed short id;
	signed char type;
	struct node **children;
	unsigned short children_count;
	collided *collisions;
	unsigned short collisions_count;

	void (*render)(struct node *this);
	actor *node_actor;
	point3d position;
	point3d position_prev;
	point3d rotation;

	void (*routine)(struct node *this);
	signed short routine_index;
	bool world_bind;
	void *properties;
	/* the node will be responsible for maintaining and cleaning its children records */
	/*	note: a scene does not require a collision table
	*  	this may be null if the scene does not implement
	* 		any objects employing collision
	* 		behavior of objects with collision in scenes
	* 		with no index is undefined
	*/
} node;

#define NT_NULL		-1

#define NR_NULL		-1
#define	NR_INIT		0
#define	NR_FREE		1
#define NR_COLLIDE	2

node *node_new(signed short id, signed int type, void (*render)(node *this), void (*routine)(node *this));
void node_addcollision(node *this, node *colliding_node, collided has_collided);
void node_clearcollisions(node *this);
void node_render(node *this);
void node_routine(node *this, signed char routine_index);
void node_free(node *this);
unsigned short node_addchildnode(node *this, node *child);
void node_prunechildnode(node *this, unsigned short index);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif /* __NODE_H__ */

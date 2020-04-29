/*
 * scene - a primitive scene graph
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"

#define sabs(a) (unsigned short) fabs((double) a)

/* ==================== Scene Creation and Destruction ==================== */

/*
 * new - make a new scene with an uninitialized node collection
 */
scene *scene_new(void)
{
	scene *this = malloc(sizeof (scene));
	this->nodes = NULL;
	this->node_count = 0;
	
	this->root_node = NULL;
	this->environment = NULL;
	this->camera = NULL;
	this->player = NULL;

	return this;
}


void scene_free(scene *this)
{
	unsigned short node_index;
	
	for (node_index = 0; node_index < this->node_count; node_index++) {
		node_routine(this->nodes[node_index], NR_FREE);
	}
	free(this->nodes);
	free(this);
	
	return;
}

/* ==================== Scene Display Settings ==================== */

/*
 * projection_new - setup the display volume in the scene, this will be passed to
 * the mode's display init
 * 
 * projection_type:
 * 	PROJECTION_ORTHAGONAL
 *	PROJECTION_FRUSTUM
 */
void scene_projection_new(scene *this, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane)
{	
	this->prj[0] = -x_axis;
	this->prj[1] = x_axis;
	this->prj[2] = -y_axis;
	this->prj[3] = y_axis;
	this->prj[4] = near_plane;
	this->prj[5] = far_plane;
	this->prj_type = type;
	
	return;
}

/* TODO: Lights, texture management, transitions */

/* ==================== Node Collection Management ==================== */

/* primary collection management */

/*
 * addnode - adds a new node to the scene with a given type and core
 * 
 * a node has a core made up of render and routine functions
 * these are implemented by a "mode-node" if you will, each game mode
 * implements its own distinct set of node objects, each "inheriting" these
 * basic constructs
 */
unsigned short scene_addnode(scene *this, signed short type, void (*render)(node *), void (*routine)(node *))
{
	unsigned short id;
	node **new_node = realloc(this->nodes, ++this->node_count * sizeof (node *));
		this->nodes = new_node;
	id = this->node_count - 1;
	
	this->nodes[id] = node_new(id, type, render, routine);
	node_routine(this->nodes[id], NR_INIT);

	return id;
}

/*
 * switchactivenode - a node with a negative ID number is inactive
 * 
 * a deactivated node's functions will cease to perform
 */
void scene_switchactivenode(scene *this, signed short node_id)
{
	unsigned short node_index = sabs(node_id);
		this->nodes[node_index]->id *= -1;
	
	return;
}

/*
 * TODO: prunenode - completely prune a node from tree
 * 
 * a pruned node is carefully removed from the scene altogether
 * pruning nodes can save space but requires both ensuring
 * the collection is realigned properly by transferring active
 * objects to a new, compact location and updating IDs as they're
 * inserted, but also ensuring the object is effectively removed
 * from any child collections it may be a part of
 * 
 * this may involve node or even actor level methods being called
 * to properly disconnect this node from any it may be related to
 * and manipulation of heavily nested child nodes is encouraged by
 * way of their parents
 */

/*
 * TODO: deletenode - completely remove a node from tree
 * 
 * delete node will simply pluck the node directly out of its slot
 * in the node tree, this method will not ensure the node
 * is removed from any child collections
 * 
 */

/* child collection management */

/*
 * setchildnode - sets a child node in the scene
 */
int scene_setchildnode(scene *this, signed short parent_node, signed short child_node)
{
	int retval = -1;
	
	if (parent_node > this->node_count)
		fprintf(stderr, "parent node %d not present in node collection\n", parent_node);
	else if (child_node > this->node_count)
		fprintf(stderr, "child node %d not present in node collection\n", child_node);
	else if (parent_node < 0)
		fprintf(stderr, "parent node %d is inactive\n", parent_node);
	else if (child_node < 0)
		fprintf(stderr, "child node %d is inactive\n", child_node);
	else if (this->nodes[parent_node] == NULL)
		fprintf(stderr, "parent node %d not defined\n", parent_node);
	else if (this->nodes[child_node] == NULL)
		fprintf(stderr, "child node %d not defined\n", child_node);
	else
		retval = node_addchildnode(this->nodes[parent_node], this->nodes[child_node]);
	
	return retval;
}

/* ==================== Bounding Box ==================== */
 
/* enforceboundingnode - enforce the scene's exterior bounding box
 * 
 *  the mode should call this between movement and the render cycle if world bounding
 *  is desired
 *  will not process for null, inactive, or unbound objects
 */
void scene_enforcebounding(scene *this)
{
	unsigned short node_index;
	
	for (node_index = 0; node_index < this->node_count; node_index++) {
		if (this->nodes[node_index] == NULL						/* deleted */
			|| this->nodes[node_index]->id < 0					/* inactive */
			|| !this->nodes[node_index]->world_bind) continue;	/* and unbound dni */
		
		if (this->nodes[node_index]->position.x < this->bounding_box[0])
			this->nodes[node_index]->position.x = this->bounding_box[0];
		else if (this->nodes[node_index]->position.x > this->bounding_box[1])
			this->nodes[node_index]->position.x = this->bounding_box[1];

		if (this->nodes[node_index]->position.y < this->bounding_box[2])
			this->nodes[node_index]->position.y = this->bounding_box[2];
		else if (this->nodes[node_index]->position.y > this->bounding_box[3])
			this->nodes[node_index]->position.y = this->bounding_box[3];
	
		if (this->nodes[node_index]->position.z < this->bounding_box[4])
			this->nodes[node_index]->position.z = this->bounding_box[4];
		else if (this->nodes[node_index]->position.z > this->bounding_box[5])
			this->nodes[node_index]->position.z = this->bounding_box[5];
	}
	
	return;
}

/* ==================== Node Manipulation ==================== */

/*
 * positionnode - positions a node relative to world normal
 */
void scene_positionnode(scene *this, signed short node_id, point3d position)
{
	if (node_id >= 0)
		this->nodes[node_id]->position = position;
	
	return;
}

/*
 * rotatenode - rotates a node relative to node normal
 */
void scene_rotatenode(scene *this, signed short node_id, point3d angle)
{
	if (node_id >= 0)
		this->nodes[node_id]->rotation = angle;
	
	return;
}


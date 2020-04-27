/*
 * scene - a primitive scene graph
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"

/* ==================== Scene Display Settings ==================== */

/*
 * projection_new - setup the display volume in the scene, this will be passed to
 * the mode's display init
 * 
 * projection_type:
 * 	PROJECTION_ORTHAGONAL
 *	PROJECTION_FRUSTUM
 */
void scene_projection_new(scene *graph, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane)
{	
	graph->prj[0] = -x_axis;
	graph->prj[1] = x_axis;
	graph->prj[2] = -y_axis;
	graph->prj[3] = y_axis;
	graph->prj[4] = near_plane;
	graph->prj[5] = far_plane;
	graph->prj_type = type;
	
	return;
}

/* TODO: Lights, texture management, transitions */

/* ==================== Node Collection Management ==================== */

/* primary collection management */

/*
 * addnode - adds a new node to the scene graph with a given type and core
 * 
 * a node has a core made up of render and routine functions
 * these are implemented by a "mode-node" if you will, each game mode
 * implements its own distinct set of node objects, each "inheriting" these
 * basic constructs
 */
signed short scene_addnode(scene *graph, signed short type, void (*render)(node *), void (*routine)(node *))
{
	signed short id;
	/* request a new slot in the node list, increment ID */
	node **new_node = realloc(graph->nodes, ++graph->node_count * sizeof (node *));
		graph->nodes = new_node;
	id = graph->node_count - 1;
	
	/* create our node and initialize it */
	graph->nodes[id] = node_new(id, type, render, routine);
	node_routine(graph->nodes[id], NR_INIT);

	return id;
}

/*
 * switchactivenode - a node with a negative ID number is inactive
 * 
 * a deactivated node's functions will cease to perform
 */
void scene_switchactivenode(scene *graph, signed short node_id)
{
	graph->nodes[node_id]->id *= -1;
	
	return;
}

/*
 * revivenode - return a node to normal operation
 * 
 * revived nodes are simply activated in their respective slots in the
 * scene, currently no memory is ever cleared for dissociated nodes
 * but this could be implemented as buffering active records then realigning
 * the memory
 * 
 * pass a negative node_id to restore an object in an inactive state
 */
void scene_revivenode(scene *graph, signed short node_id)
{
	graph->nodes[node_id]->id = node_id;
	
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
void scene_setchildnode(scene *graph, signed int parent, signed int child)
{
	if (parent > graph->node_count)
		fprintf(stderr, "parent node %d not in node collection\n", parent);
	else if (child > graph->node_count)
		fprintf(stderr, "child node %d not in node collection\n", child);
	else if (graph->nodes[parent] == NULL)
		fprintf(stderr, "parent node %d not defined\n", parent);
	else if (graph->nodes[child] == NULL)
		fprintf(stderr, "child node %d not defined\n", child);
	else
		node_addchildnode(graph->nodes[parent], graph->nodes[child]);
	
	return;
}

/* ==================== Node Collision ==================== */
 
/* enforceboundingnode - enforce the scene's exterior bounding box on a given node
 * 
 * it is the node's decision whether it will rely on the scene to bind it
 * so the node must call scene bounding in it's collision routine, ideally last,
 * even if this causes it to clip into another object, frequent scene bounding
 * correction is encouraged in complex activities near scene bounds
 */
bool scene_enforceboundingnode(scene *graph, signed short node_id)
{
	if (graph->nodes[node_id]->position.x < graph->bounding_box[0])
		graph->nodes[node_id]->position.x = graph->bounding_box[0];
	else if (graph->nodes[node_id]->position.x > graph->bounding_box[1])
		graph->nodes[node_id]->position.x = graph->bounding_box[1];

	if (graph->nodes[node_id]->position.y < graph->bounding_box[2])
		graph->nodes[node_id]->position.y = graph->bounding_box[2];
	else if (graph->nodes[node_id]->position.y > graph->bounding_box[3])
		graph->nodes[node_id]->position.y = graph->bounding_box[3];
	
	if (graph->nodes[node_id]->position.z < graph->bounding_box[4])
		graph->nodes[node_id]->position.z = graph->bounding_box[4];
	else if (graph->nodes[node_id]->position.z > graph->bounding_box[5])
		graph->nodes[node_id]->position.z = graph->bounding_box[5];
	
	return true;
}

/* ==================== Node Manipulation ==================== */

/*
 * positionnode - positions a node relative to world normal
 */
void scene_positionnode(scene *graph, signed short node_id, point3d position)
{
	graph->nodes[node_id]->position = position;
	
	return;
}

/*
 * rotatenode - rotates a node relative to node normal
 */
void scene_rotatenode(scene *graph, signed short node_id, point3d angle)
{
	graph->nodes[node_id]->rotation = angle;
	
	return;
}


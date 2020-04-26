/*
 * node - a single node in a scene graph
 */
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node *node_new(signed short id, signed int type, void (*render)(node *this), void (*routine)(node *this))
{
	node *new_node = malloc(sizeof (node));
	new_node->id = id;
	new_node->type = type;
	new_node->node_actor = NULL;
	new_node->children = NULL;
	new_node->children_count = 0;
	new_node->render = render;
	new_node->routine = routine;
	
	return new_node;
}

void node_render(node *this)
{
	if (this == NULL)
		fputs("render: undefined node passed\n", stderr);
	else if (this->render == NULL)
		fprintf(stderr, "node %d is undefined or not rendering\n", this->id);
	else if (this->id < 0)
		;	/* do nothing, node is inactive */
	else
		this->render(this);
	
	return;
}

void node_routine(node *this, signed char routine_index)
{
	if (this == NULL)
		fputs("routine: undefined node passed\n", stderr);
	else if (this->routine == NULL)
		fprintf(stderr, "node %d is undefined or has no routine\n", this->id);
	else if (this->id < 0)
		;	/* do nothing, node is inactive */
	else if (routine_index == NR_NULL)
		;	/* do nothing, null routine */
	else {
		this->routine_index = routine_index;
		this->routine(this);
	}
	
	return;
}

void node_free(node *this)
{
	if (this == NULL)
		fprintf(stderr, "node %d null or freed\n", this->id);
	else {
		if (this->node_actor != NULL)
			actor_routine(this->node_actor, AR_FREE);
		if (this->children != NULL)
			free(this->children);
		free(this);
	}
	
	return;
}

/* addchildnode - add one node in the graph to the child collection of another
 * 
 * expands and inserts a node into the child collection of an existing node
 * 
 * unlike nodes, a child node does not have an id, simply a position
 * in the index, as it is just a pointer to the node in question
 * a node is responsible for managing its children, but this will hand it
 * an index if it asks nicely
 */
unsigned short node_addchildnode(node *this, node *child)
{
	node **children = realloc(this->children, ++this->children_count * sizeof (node *));
	this->children = children;
	this->children[this->children_count - 1] = child;
	
	return this->children_count - 1;
}

/*
 * prunechildnode - remove a child node from a collection
 * 
 * carefully removes a child node from the collection at
 * the given index
 */
void node_prunechildnode(node *this, unsigned int index)
{
	int child;
	int newpos = 0;
	node **pruned_children = malloc((this->children_count - 1) * sizeof (node *));
	
	for (child = 0; child = this->children_count; child++) {
		if (child == index)
			continue;
		pruned_children[newpos++] = this->children[child];
	}
	
	free(this->children);
	this->children = pruned_children;
	this->children_count--;
	
	return;
}

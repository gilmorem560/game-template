/*
 * scene - a primitive scene graph
 */
#include "scene.h"

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

signed short scene_addnode(scene *graph, signed short type, bool type_router, signed char routine, void (*router)(void))
{
	signed short id;
	graph->nodes = realloc(graph->nodes, ++graph->node_count);
	id = graph->node_count - 1;
	graph->nodes[id] = malloc(sizeof (node));
	graph->nodes[id]->actor_entry.id = id;
	graph->nodes[id]->actor_entry.actor_obj = malloc(sizeof (actor));
	graph->nodes[id]->actor_entry.actor_obj->type = type;
	graph->nodes[id]->actor_entry.actor_obj->type_router = type_router;
	graph->nodes[id]->actor_entry.actor_obj->routine = ACTOR_ROUTINE_NULL;
	graph->nodes[id]->actor_entry.actor_obj->router = NULL;
	graph->nodes[id]->children = NULL;
	graph->nodes[id]->children_count = 0;
	graph->nodes[id]->vertex_array = NULL;
	graph->nodes[id]->normal_array = NULL;
	graph->nodes[id]->color_array = NULL;
	graph->nodes[id]->vao_indicies = NULL;
	
	return id;
}

void scene_enforceboundingnode(scene *graph, signed short node_id)
{
	if (graph->nodes[node_id]->position[0] < graph->bounding_box[0])
		graph->nodes[node_id]->position[0] = graph->bounding_box[0];
	else if (graph->nodes[node_id]->position[0] > graph->bounding_box[1])
		graph->nodes[node_id]->position[0] = graph->bounding_box[1];
	
	if (graph->nodes[node_id]->position[1] < graph->bounding_box[2])
		graph->nodes[node_id]->position[1] = graph->bounding_box[2];
	else if (graph->nodes[node_id]->position[1] > graph->bounding_box[3])
		graph->nodes[node_id]->position[1] = graph->bounding_box[3];
	
	if (graph->nodes[node_id]->position[2] < graph->bounding_box[4])
		graph->nodes[node_id]->position[2] = graph->bounding_box[4];
	else if (graph->nodes[node_id]->position[2] > graph->bounding_box[5])
		graph->nodes[node_id]->position[2] = graph->bounding_box[5];
	
	return;
}

void scene_setchildnode(scene *graph, signed int parent, signed int child)
{
	graph->nodes[parent]->children = realloc(graph->nodes[parent]->children, ++graph->nodes[parent]->children_count);
	graph->nodes[parent]->children[graph->nodes[parent]->children_count - 1] = graph->nodes[child];
	
	return;
}

void scene_skinnode(scene *graph, signed int node_id, GLdouble *verticies, GLdouble *normals, GLdouble *colors, GLubyte *vaos)
{
	graph->nodes[node_id]->vertex_array = verticies;
	graph->nodes[node_id]->normal_array = normals;
	graph->nodes[node_id]->color_array = colors;
	graph->nodes[node_id]->vao_indicies = vaos;
	
	return;
}

void scene_positionnode(scene *graph, signed short node_id, double xpos, double ypos, double zpos)
{
	graph->nodes[node_id]->position[0] = xpos;
	graph->nodes[node_id]->position[1] = ypos;
	graph->nodes[node_id]->position[2] = zpos;
	
	return;
}

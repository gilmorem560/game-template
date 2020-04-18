/*
 * scene - a primitive scene graph
 */
#include "scene.h"

void scene_projection_new(scene *graph, projection_type type, double x_axis, double y_axis, double near_plane, double far_plane)
{	
	/* start fresh */
	if (graph->prj == NULL) {
		free(graph->prj);
	}
	
	graph->prj = malloc(6 * sizeof (GLdouble));
	graph->prj[0] = -x_axis;
	graph->prj[1] = x_axis;
	graph->prj[2] = -y_axis;
	graph->prj[3] = y_axis;
	graph->prj[4] = near_plane;
	graph->prj[5] = far_plane;
	graph->prj_type = type;
	
	return;
}

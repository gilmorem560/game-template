/*
 * scene - a primitive scene graph
 */
#include "scene.h"

void scene_projection_new(scene *graph, projection_type type, double x_axis, double y_axis, double near, double far)
{	
	/* start fresh */
	if (graph->prj == NULL) {
		free(graph->prj);
	}
	
	graph->prj = (GLdouble *) malloc(6 * sizeof (GLdouble));
	graph->prj[0] = -x_axis;
	graph->prj[1] = x_axis;
	graph->prj[2] = -y_axis;
	graph->prj[3] = y_axis;
	graph->prj[4] = near;
	graph->prj[5] = far;
	graph->prj_type = type;
	
	return;
}

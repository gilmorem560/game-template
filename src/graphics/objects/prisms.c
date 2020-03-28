/*
 * prisms - Simple 3D Shapes
 */
#include <stdlib.h>

/* graphics handler */
#include "../contexts/glcontext.h"

/* basic objects */
#include "../primitives/coord.h"
#include "../primitives/prim.h"
 
/*
 * quadprism - regular quad-based prism
 * x - length
 * y - width
 * z - height
 */
void quadprism(double x, double y, double z)
{
	int i;
	
	point3d points[8] = {
		{x, y, z}
		,{x, y, -z}
		,{x, -y, z}
		,{x, -y, -z}
		,{-x, y, z}
		,{-x, y, -z}
		,{-x, -y, z}
		,{-x, -y, -z}
	};
	quad3d *quads[6];
	
	/* create our primitives */
	quads[0] = new_poly3d(4, points[1], points[0], points[2], points[3]);
	quads[1] = new_poly3d(4, points[0], points[4], points[6], points[2]);
	quads[2] = new_poly3d(4, points[4], points[5], points[7], points[6]);
	quads[3] = new_poly3d(4, points[5], points[1], points[3], points[7]);
	quads[4] = new_poly3d(4, points[1], points[5], points[4], points[0]);
	quads[5] = new_poly3d(4, points[2], points[6], points[7], points[3]);
	
	/* drawing models */
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_FLAT);
	
	/* draw them */
	draw_quad3d(quads[0], 1.0, 0.0, 0.0);
	draw_quad3d(quads[1], 0.0, 1.0, 0.0);
	draw_quad3d(quads[2], 1.0, 0.0, 1.0);
	draw_quad3d(quads[3], 1.0, 1.0, 0.0);
	draw_quad3d(quads[4], 0.0, 0.0, 1.0);
	draw_quad3d(quads[5], 0.0, 1.0, 1.0);
	
	/* cleanup */
	for (i = 0; i < 6; i++) {
		free(quads[i]);
	}
}

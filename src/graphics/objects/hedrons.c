/*
 * hedrons - Simple 3D Shapes
 */
#include <stdlib.h>

/* graphics handler */
#include "../contexts/glcontext.h"

/* basic objects */
#include "../primitives/coord.h"
#include "../primitives/prim.h"

void octahedron(double x, double y, double z)
{
	int i;
	point3d points[6] = {
		{0, 0, 0}
		,{0, 0, 0}
		,{0, 0, 0}
		,{0, 0, 0}
		,{0, 0, 0}
		,{0, 0, 0}
	};
	tri3d *triangles[8];
	glShadeModel(GL_FLAT);
	
	/* create our points */
	points[0].x = x;
	points[1].x = -x;
	points[2].y = y;
	points[3].y = -y;
	points[4].z = z;
	points[5].z = -z;
	
	/* create our objects */
	triangles[0] = new_poly3d(3, points[0], points[2], points[4]);
	triangles[1] = new_poly3d(3, points[0], points[2], points[5]); 
	triangles[2] = new_poly3d(3, points[0], points[3], points[4]); 
	triangles[3] = new_poly3d(3, points[0], points[3], points[5]); 
	triangles[4] = new_poly3d(3, points[1], points[2], points[4]); 
	triangles[5] = new_poly3d(3, points[1], points[2], points[5]); 
	triangles[6] = new_poly3d(3, points[1], points[3], points[4]); 
	triangles[7] = new_poly3d(3, points[1], points[3], points[5]); 
	
	/* draw them */
	draw_tri3d(triangles[0], 1.0, 0.0, 0.0);
	draw_tri3d(triangles[1], 0.0, 1.0, 0.0);
	draw_tri3d(triangles[2], 0.0, 0.0, 1.0);
	draw_tri3d(triangles[3], 1.0, 1.0, 0.0);
	draw_tri3d(triangles[4], 0.0, 1.0, 1.0);
	draw_tri3d(triangles[5], 1.0, 0.0, 1.0);
	draw_tri3d(triangles[6], 1.0, 1.0, 1.0);
	draw_tri3d(triangles[7], 0.0, 0.0, 0.0);
	
	/* cleanup */
	for (i = 0; i < 8; i++) {
		free(triangles[i]);
	}
	
	glShadeModel(GL_SMOOTH);
}

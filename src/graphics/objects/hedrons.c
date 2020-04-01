/*
 * hedrons - simple 3D Shapes
 */
#include <stdlib.h>
#include <math.h>

/* graphics handler */
#include "../contexts/glcontext.h"

/* basic objects */
#include "../primitives/coord.h"
#include "../primitives/prim.h"

/*
 * tetrahedron - regular four-faced hedron
 * n - normal vector length
 */
void tetrahedron(double n)
{
	int i;
	double normalDepth;
	double normalLength;
	double normalFactor = sqrt(3.0) / 2.0;
	double normalDX;
	double normalDZ;
	
	point3d points[4] = {
		{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
	};
	tri3d *triangles[4];
	glShadeModel(GL_FLAT);
	
	/* create our points */
	normalDepth = n / 2.0;
	normalLength = normalFactor * n;
	normalDX = normalLength * sqrt(3.0) / 2.0;
	normalDZ = normalLength / 2.0;
	
	points[0].y = n;
	points[1].y = -normalDepth;
	points[2].y = -normalDepth;
	points[3].y = -normalDepth;
	
	/* todo - may be swapped */
	points[1].z = -normalLength;
	points[2].z = normalDZ;
	points[3].z = normalDZ;
	
	points[2].x = -normalDX;
	points[3].x = normalDX;
	
	/* create our primitives */
	triangles[0] = new_poly3d(3, points[0], points[2], points[3]);
	triangles[1] = new_poly3d(3, points[0], points[3], points[1]);
	triangles[2] = new_poly3d(3, points[0], points[1], points[2]);
	triangles[3] = new_poly3d(3, points[3], points[2], points[1]);
	
	/* drawing models */
	glMatrixMode(GL_MODELVIEW);
	
	/* draw them */
	draw_tri3d(triangles[0], 1.0, 0.0, 0.0);
	draw_tri3d(triangles[1], 0.0, 1.0, 0.0);
	draw_tri3d(triangles[2], 0.0, 0.0, 1.0);
	draw_tri3d(triangles[3], 1.0, 1.0, 0.0);
	
	/* cleanup */
	for (i = 0; i < 4; i++) {
		free(triangles[i]);
	}
}

/*
 * octahedron - regular eight-faced hedron
 * x - width
 * y - height
 * z - depth
 */
void octahedron(double x, double y, double z)
{
	int i;
	point3d points[6] = {
		{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
		,{0.0, 0.0, 0.0}
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
	
	/* create our primitives */
	triangles[0] = new_poly3d(3, points[0], points[4], points[2]);
	triangles[1] = new_poly3d(3, points[0], points[2], points[5]); 
	triangles[2] = new_poly3d(3, points[0], points[5], points[3]); 
	triangles[3] = new_poly3d(3, points[0], points[3], points[4]); 
	triangles[4] = new_poly3d(3, points[1], points[2], points[4]); 
	triangles[5] = new_poly3d(3, points[1], points[5], points[2]); 
	triangles[6] = new_poly3d(3, points[1], points[3], points[5]); 
	triangles[7] = new_poly3d(3, points[1], points[4], points[3]); 
	
	/* drawing models */
	glMatrixMode(GL_MODELVIEW);
	
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
}

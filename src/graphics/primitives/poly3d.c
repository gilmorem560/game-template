/*
 * poly3d - basic polygon in 3d space
 */
#include <stdlib.h>
#include <stdarg.h>

#include "../../../config.h"

#ifdef  HAVE_GL_GL_H    /* OpenGL libraries */
#include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#include <OpenGL/gl.h>
#endif /* HAVE_GL_GL_H, HAVE_OPENGL_GL_H */

#include "coord.h"  /* coordinate objects */
#include "prim.h"   /* primitive shapes */

/*
 * new_poly3d - create a new polygon from an indeterminate number of points
 */
poly3d *new_poly3d(unsigned char point_count, ...)
{
    va_list points;
    poly3d *newpoly = NULL;

    /* need more than two points for a polygon */
    if (point_count >= 3) {
        newpoly = (poly3d *) calloc(1, sizeof (poly3d));
        if (newpoly != NULL) {
            newpoly->point_count = point_count;
            newpoly->points = (point3d *) calloc(point_count, sizeof (point3d));
            if (newpoly->points != NULL) {
                va_start(points, point_count);
                do {
                    newpoly->points[point_count - 1] = va_arg(points, point3d);
                } while (point_count-- > 1);
            }
        }
    }

    va_end(points);

    return newpoly;
}

/*
 * draw_tri3d - draw a triangle
 */
void draw_tri3d(tri3d *poly, double r, double g, double b)
{
    int a = 0;
    glBegin(GL_TRIANGLES);
        glColor3d(r, g, b);
        for (a = 0; a < 3; a++) {
            glVertex3d(poly->points[a].x, poly->points[a].y, poly->points[a].z);
        }
    glEnd();
    
    return;
}

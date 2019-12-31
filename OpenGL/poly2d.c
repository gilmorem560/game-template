/*
 * poly2 - basic polygon in 2d space
 */
#include <stdlib.h>
#include <stdarg.h>

#include "coord.h"  /* coordinate objects */
#include "prim.h"   /* primitive shapes */

/*
 * new_poly2d - create a new polygon from an indeterminate number of points
 */
poly2d *new_poly2d(unsigned char point_count, ...)
{
    va_list points;
    poly2d *newpoly = NULL;

    /* need more than two points for a polygon */
    if (point_count > 2) {
        newpoly = (poly2d *) calloc(1, sizeof (poly2d));
        if (newpoly != NULL) {
            newpoly->point_count = point_count;
            newpoly->points = (point2d *) calloc(point_count, sizeof (point2d));
            if (newpoly->points != NULL) {
                va_start(points, point_count);
                do {
                    newpoly->points[point_count - 1] = va_arg(points, point2d);
                } while (point_count-- > 1);
            }
        }
    }

    va_end(points);

    return newpoly;
}
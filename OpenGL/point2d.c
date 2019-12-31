/*
 * point2d - 2d coordinate
 */
#include <math.h>

#include "coord.h"

/*
 * dist2d - distance between two 2d coordinates
 */
double dist2d(point2d a, point2d b) {
    double dist = 0.0;
    double xdiff = 0.0;
    double ydiff = 0.0;

    xdiff = (double) a.x - (double) b.x;
    ydiff = (double) a.y - (double) b.y;

    dist = sqrt((xdiff * xdiff) + (ydiff * ydiff));

    return dist;
}
/*
 * coord - coordinate related objects and functions
 */
#ifndef __COORD_H__
#define __COORD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 2d space */
typedef struct point2d {
    double x;
    double y;
} point2d;
typedef struct grid2d {
    double x;
    double y;
} grid2d;

#define pointdistance2d(a, b)	sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y))

/* 3d space */
typedef struct point3d {
    double x;
    double y;
    double z;
} point3d;
typedef struct grid3d {
    double x;
    double y;
    double z;
} grid3d;

#define pointdistance3d(a, b)	sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z))

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COORD_H__ */

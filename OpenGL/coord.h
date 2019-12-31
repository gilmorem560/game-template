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
    signed int x;
    signed int y;
} point2d;
typedef struct grid2d {
    int x;
    int y;
} grid2d;

/* 2d point operations */
double dist2d(point2d a, point2d b);

/* 3d space */
typedef struct point3d {
    signed int x;
    signed int y;
    signed int z;
} point3d;
typedef struct grid3d {
    int x;
    int y;
    int z;
} grid3d;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COORD_H__ */
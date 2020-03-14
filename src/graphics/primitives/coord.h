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

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COORD_H__ */

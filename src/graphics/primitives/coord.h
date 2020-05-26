/*
 * coord - coordinate related objects and functions
 */
#ifndef __COORD_H__
#define __COORD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 2d space */
typedef struct dim2 {	/* two dimensional construct */
} dim2;
typedef dim2 point2d;
typedef dim2 grid2d;

#define pointdistance2d(a, b)	sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y))

/* 3d space */
typedef struct dim3 {	/* three dimensional construct */
	double x;
	double y;
	double z;
} dim3;
typedef dim3 point3d;
typedef dim3 grid3d;

#define pointdistance3d(a, b)	sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z))

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __COORD_H__ */

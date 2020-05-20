/*
 * vector_calcs - vector calculations
 */
#ifndef __VECTOR_CALCS_H__
#define __VECTOR_CALCS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* a vector */
typedef struct vect {
	double mag;
	double ang;
} vect;

/* vector components */
typedef struct vect_component {
	double x;
	double y;
	double z;
} vect_component;

typedef vect_component vect_comp2d;
typedef vect_component vect_comp3d;
	
void veccomp2d_calc(double magnitude, double angle, vect_comp2d *new);
double vecang2d_calc(double x_comp, double y_comp);
#define vecmag2d_calc(x,y) sqrt((x*x),(y*y))
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __VECTOR_CALCS_H__ */

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
} vect_component;
	
void veccomp2d_calc(double magnitude, double angle, vect_component *new);
double vecang2d_calc(double x_comp, double y_comp);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __VECTOR_CALCS_H__ */

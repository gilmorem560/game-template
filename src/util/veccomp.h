/*
 * veccomp - vector components
 */
#ifndef __VECCOMP_H__
#define __VECCOMP_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
typedef struct veccomp2d {
	double x;
	double y;
} veccomp2d;
	
void veccomp2d_calc(double magnitude, double angle, veccomp2d *new);
double vecang2d_calc(double x_comp, double y_comp);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __VECCOMP_H__ */

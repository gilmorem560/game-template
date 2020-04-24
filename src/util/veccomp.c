/*
 * veccomp - vector components
 */
#include "macros.h"
#include "veccomp.h"

/*
 * veccomp2d_calc - calculate the components of a 2D vector with given magnitude and angle
 */
void veccomp2d_calc(double magnitude, double angle, veccomp2d *new)
{
	if (angle <= -270) {
		new->x = -sin(degtorad(fmod(angle, 90)));
		new->y = cos(degtorad(fmod(angle, 90)));
	} else if (angle <= -180) {
		new->x = -cos(degtorad(fmod(angle, 90)));
		new->y = -sin(degtorad(fmod(angle, 90)));
	} else if (angle <= -90) {
		new->x = sin(degtorad(fmod(angle, 90)));
		new->y = -cos(degtorad(fmod(angle, 90)));
	} else if (angle < 0) {
		new->x = cos(degtorad(fmod(angle, 90)));
		new->y = sin(degtorad(fmod(angle, 90)));
	} else if (angle < 90) {
		new->x = cos(degtorad(fmod(angle, 90)));
		new->y = sin(degtorad(fmod(angle, 90)));
	} else if (angle < 180) {
		new->x = -sin(degtorad(fmod(angle, 90)));
		new->y = cos(degtorad(fmod(angle, 90)));
	} else if (angle < 270) {
		new->x = -cos(degtorad(fmod(angle, 90)));
		new->y = -sin(degtorad(fmod(angle, 90)));
	} else {
		new->x = sin(degtorad(fmod(angle, 90)));
		new->y = -cos(degtorad(fmod(angle, 90)));
	}
	
	new->x *= magnitude;
	new->y *= magnitude;
		
	return;
}

/*
 * vecang2d_calc - calculate the angle from normal for a displacement using arctangent
 */
double vecang2d_calc(double x_comp, double y_comp)
{
	double angle;
	double abs_x_comp = fabs(x_comp);
	double abs_y_comp = fabs(y_comp);
	
	if (x_comp == 0 && y_comp == 0)
		return 0.0;
	else if (x_comp == 0) {
		if (y_comp > 0)
			return 0.0;
		else
			return 180.0;
	} else if (y_comp == 0) {
		if (x_comp > 0)
			return 90.0;
		else
			return -90.0;
	}
	
	if (x_comp > 0 && y_comp > 0) {
		if (abs_y_comp > abs_x_comp)
			return radtodeg(atan(abs_x_comp / abs_y_comp));
		else if (abs_y_comp < abs_x_comp)
			return 90.0 - radtodeg(atan(abs_y_comp / abs_x_comp));
		else
			return 45.0;
	} else if (x_comp > 0 && y_comp < 0) {
		if (abs_x_comp > abs_y_comp)
			return radtodeg(atan(abs_y_comp / abs_x_comp)) + 90.0;
		else if (abs_x_comp < abs_y_comp)
			return 180.0 - radtodeg(atan(abs_x_comp / abs_y_comp));
		else
			return 135.0;
	} else if (x_comp < 0 && y_comp < 0) {
		if (abs_y_comp > abs_x_comp)
			return -180.0 + radtodeg(atan(abs_x_comp / abs_y_comp));
		else if (abs_y_comp < abs_x_comp)
			return -90.0 - radtodeg(atan(abs_y_comp / abs_x_comp));
		else
			return -135.0;
	} else {
		if (abs_x_comp > abs_y_comp)
			return -90.0 + radtodeg(atan(abs_y_comp / abs_x_comp));
		else if (abs_x_comp < abs_y_comp)
			return -radtodeg(atan(abs_x_comp / abs_y_comp));
		else
			return -45.0;
	}
	
	return angle;
}

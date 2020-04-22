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

/*
 * camera - the camera in our world
 */
#include "../nodes.h"

/*
 * camera_refresh - update the position of our camera in world space
 */
void camera_refresh(node *this)
{
	vect_component xrot = { 0.0, 0.0 };
	veccomp2d_calc(1.0, this->rotation.x, &xrot);
	
	glRotated(this->rotation.x, 0.0, 1.0, 0.0);
	glRotated(this->rotation.y, xrot.x, 0.0, xrot.y);
	glTranslated(-this->position.x, -this->position.y, this->position.z);
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
}

void camera_routine(node *this, node *player)
{
	vect_comp3d camera_dist_c;
	double camera_dist_z_adj;
	double camera_dist;
	double camera_dist_planar;
	vect_component camera_xz = { 0.0, 0.0 };
	
	/* determine distance */
	camera_dist_c.x = player->position.x - this->position.x;
	camera_dist_c.y = player->position.y - this->position.y;
	camera_dist_c.z = player->position.z - this->position.z;
	camera_dist_z_adj = sqrt((camera_dist_c.x * camera_dist_c.x) + (camera_dist_c.z * camera_dist_c.z));

	/* rotate camera */
	this->rotation.x = vecang2d_calc(camera_dist_c.x, camera_dist_c.z);
	this->rotation.y = -vecang2d_calc(camera_dist_c.y, camera_dist_z_adj);
	
	/* move camera */
	camera_dist = pointdistance3d(this->position, player->position);
	if (camera_dist > CAMERA_DIST_MAX) {
		this->position.x += (camera_dist - CAMERA_DIST_MAX) * (camera_dist_c.x / camera_dist);
		this->position.y += (camera_dist - CAMERA_DIST_MAX) * (camera_dist_c.y / camera_dist);
		this->position.z += (camera_dist - CAMERA_DIST_MAX) * (camera_dist_c.z / camera_dist);
	} else if (camera_dist < CAMERA_DIST_MIN) {
		this->position.x -= (CAMERA_DIST_MIN - camera_dist) * (camera_dist_c.x / camera_dist);
		this->position.y -= (CAMERA_DIST_MIN - camera_dist) * (camera_dist_c.y / camera_dist);
		this->position.z -= (CAMERA_DIST_MIN - camera_dist) * (camera_dist_c.z / camera_dist);
	}
	
	/* normalize angles */
	this->rotation.x = fmod(this->rotation.x, 360.0);
	this->rotation.y = fmod(this->rotation.y, 360.0);
	
	return;
}

/*
 * player - the player is you!
 */
#include "../nodes.h"

dim3 player_accel;
dim3 player_vel;

bool player_has_orbit;
bool trigger_jump;

static int orbit_node;
static int orbit_child_index;

static bool standing_on_surface;

void player_init(node *this)
{
	this->node_actor = at_tet_new();
	actor_routine(this->node_actor, AR_INIT);
	
	player_has_orbit = false;
	player_vel.x = 0.0;
	player_vel.y = 0.0;
	player_vel.z = 0.0;
	player_accel.x = 0.0;
	player_accel.y = -0.03;
	player_accel.z = 0.0;
	orbit_node = 0;
	orbit_child_index = 0;
	
	return;
}

void player_free(node *this)
{
	node_free(this);
	
	return;
}

/* 
 * TODO: tidy into a generic bounding box collision handler
 */
bool player_to_box(node *player, node *box)
{
	double dist_x, dist_y, dist_z;
	double ang_x;
	bool box_inside_x = false;
	bool box_inside_y = false;
	bool box_inside_z = false;
	bool box_collided = false;
	bool touched_x = false;
	bool touched_y = false;
	bool touched_z = false;
	bool standing = false;
	
	/* detect incursion */
	if (player->position.x > box->position.x - 0.6
		&& player->position.x < box->position.x + 0.6) {
		box_inside_x = true;
	} else
		box_inside_x = false;

	if (player->position.y > box->position.y - 0.6
		&& player->position.y < box->position.y + 0.6) {
		box_inside_y = true;
	} else
		box_inside_y = false;

	if (player->position.z > box->position.z - 0.6
		&& player->position.z < box->position.z + 0.6) {
		box_inside_z = true;
	} else
		box_inside_z = false;

	if (box_inside_x && box_inside_y && box_inside_z)
		box_collided = true;
	
	/* determine face of collision */
	if (box_collided) {
		dist_x = player->position_prev.x - box->position.x;
		dist_y = player->position_prev.y - box->position.y;
		dist_z = player->position_prev.z - box->position.z;
		ang_x = vecang2d_calc(dist_z, dist_y);
		if ((ang_x > 45.0 && ang_x < 135.0) 
			|| (ang_x > -135.0 && ang_x < -45.0))
		{
			if (fabs(dist_x) > fabs(dist_z))
				touched_x = true;
			else
				touched_z = true;
		} else {
			if (fabs(dist_x) > fabs(dist_y))
				touched_x = true;
			else
				touched_y = true;
		}
	}
	
	/* place at point of collision */
	if (touched_x) {
		if (dist_x < 0)
			player->position.x = box->position.x - 0.6;
		else
			player->position.x = box->position.x + 0.6;
	} else if (touched_y) {
		if (dist_y < 0)
			player->position.y = box->position.y - 0.6;
		else {
			player->position.y = box->position.y + 0.6;
			standing = true;
		}
		player_vel.y = 0.0;
	} else if (touched_z) {
		if (dist_z < 0)
			player->position.z = box->position.z - 0.6;
		else
			player->position.z = box->position.z + 0.6;
	}

	return standing;
}

/*
 * collision - calculate collisions with objects
 */
void player_collision(node *this)
{
	collided has_collided = {0, 0, 0};
	unsigned short index;
	unsigned short node;
	bool got_triangle = false;
	bool standing_on_ground = false;
	bool standing_on_box = false;
	
	/* act on previous collisions by object type */
	for (index = 0; index < this->collisions_count; index++) {
		node = this->collisions[index].id;
		switch (graph->nodes[node]->type) {
		case NT_ENVIRONMENT:
			if (this->collisions[index].x)
				this->position.x = this->collisions[index].x * 2.9;
			if (this->collisions[index].y) {
				this->position.y = this->collisions[index].y * 2.9;			
				standing_on_ground = true;
				player_vel.y = 0.0;
			}
			if (this->collisions[index].z < 0)
				this->position.z = -11.0;
			else if (this->collisions[index].z > 0)
				this->position.z = -1.1;
			break;
		default:
			break;
		}
	}
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	node_clearcollisions(this);
	
	/* calculate collisions with stuff and notify them */
	for (index = sabs(this->id); index < graph->node_count; index++) {
		switch (graph->nodes[index]->type) {
		case NT_BOX:
				if (fabs(pointdistance3d(this->position,graph->nodes[index]->position)) > 1.0)
					break;	/* don't waste cycles calculating a box we're far away from */
				standing_on_box |= player_to_box(this, graph->nodes[index]);
				break;
		case NT_COLLECTIBLE:
			/* detect incursion */
			if ((this->position.x < graph->nodes[index]->position.x + 0.3 && this->position.x > graph->nodes[index]->position.x - 0.3)
				&& (this->position.y < graph->nodes[index]->position.y + 0.3 && this->position.y > graph->nodes[index]->position.y - 0.3)
				&& (this->position.z < graph->nodes[index]->position.z + 0.3 && this->position.z > graph->nodes[index]->position.z - 0.3)) {
				
				has_collided.x = 1;
				node_addcollision(graph->nodes[index], this, has_collided);
				got_triangle = true;
			}
			break;
		default:
			break;
		}
		has_collided.x = 0;
		has_collided.y = 0;
		has_collided.z = 0;
	}

	standing_on_surface = standing_on_ground | standing_on_box;

	/* act */
	if (got_triangle)
		show_triangle = true;
	/* TODO: Above should notify of collision with boxes, but action should defer until all are calculated */
	
	return;
}

void player_addorbit(node *this)
{
	orbit_node = scene_addnode(graph, NT_ORBIT, orbit_render, orbit_routine);
	scene_positionnode(graph, orbit_node, this->position);
	scene_rotatenode(graph, orbit_node, this->rotation);
	orbit_child_index = scene_setchildnode(graph, this->id, orbit_node);

	return;
}

void player_processinput(node *this)
{
	/* motion */
	if (input_mask & IM_UP) player_vel.z += motion_constant;
	if (input_mask & IM_DOWN) player_vel.z -= motion_constant;
	if (input_mask & IM_LEFT) player_vel.x -= motion_constant;
	if (input_mask & IM_RIGHT) player_vel.x += motion_constant;
	if ((input_mask & IM_ACTION1) && standing_on_surface) {player_vel.y = 0.35; standing_on_surface = false;}
	if (input_mask & IM_ACTION2) player_has_orbit = true;
	
	#ifdef HAVE_LIBEVDEV_LIBEVDEV_H
	/* x - jump */			if ((pad_pressed & (1 << PAD_B)) && standing_on_surface) {player_vel.y = 0.35; standing_on_surface = false;}
	/* motion*/
							if (pad_held & (1 << PAD_UP)) player_vel.z += motion_constant;
							if (pad_held & (1 << PAD_DOWN)) player_vel.z -= motion_constant;
							if (pad_held & (1 << PAD_LEFT)) player_vel.x -= motion_constant;
							if (pad_held & (1 << PAD_RIGHT)) player_vel.x += motion_constant;
	#endif /* HAVE_LIBEVDEV_LIBEVDEV_H */

	if (player_has_orbit && orbit_node == 0) {
		player_addorbit(this);
	}
	
	input_mask = 0;
	
	return;
}

void player_applyconstraints(node *this)
{
	unsigned int child;
	vect_component orbit_comps = { 0.0, 0.0 };
	vect_component camera_xz = { 0.0, 0.0 };
	
	/* determine current x normal */ 
	veccomp2d_calc(1.0, graph->camera->rotation.x, &camera_xz);
	
	/* move based on velocity */
	/* motion relative to camera angle */
	if (player_vel.z) {
		this->position.x += player_vel.z * camera_xz.y;
		this->position.z += player_vel.z * camera_xz.x;
		if (player_vel.z > 0.0)
			this->rotation.x = -graph->camera->rotation.x;
		else
			this->rotation.x = 540.0 - graph->camera->rotation.x;
		player_vel.z = 0.0;
	}
	if (player_vel.x) {
		if (this->position.z > graph->camera->position.z) {
			veccomp2d_calc(player_vel.x, graph->camera->rotation.x, &camera_xz);
			this->position.x += camera_xz.x;
			this->position.z -= camera_xz.y;
		} else {
			veccomp2d_calc(-player_vel.x, graph->camera->rotation.x, &camera_xz);
			this->position.x -= camera_xz.x;
			this->position.z += camera_xz.y;
		}
		if (player_vel.x > 0.0)
			this->rotation.x = -graph->camera->rotation.x - 90.0;
		else
			this->rotation.x = -graph->camera->rotation.x + 90.0;
		player_vel.x = 0.0;
	}
	
	/* handle children */
	if (this->children_count > 0 && this->children != NULL) {
		for (child = 0; child < this->children_count; child++) {
			switch (this->children[child]->type) {
			case NT_ORBIT:
				veccomp2d_calc(0.2, -this->rotation.x, &orbit_comps);
				this->children[child]->position.x = this->position.x - orbit_comps.y;
				this->children[child]->position.y = this->position.y;
				this->children[child]->position.z = this->position.z - orbit_comps.x;
				node_routine(this->children[child], NR_ORBIT_CONSTRAINT);
				break;
			default:
				break;
			}
		}
	}
	
	/* apply acceleration to velocity */
	player_vel.x = 0.0;				/* TODO: Control applies momentary acceleration */
	player_vel.y += player_accel.y;
	player_vel.z = 0.0;				/* TODO: Control applies momentary acceleration */

	/* apply velocity to position */
	this->position.y += player_vel.y;
	
	/* normalize angles */
	this->rotation.x = fmod(this->rotation.x, 360.0);
	this->rotation.y = fmod(this->rotation.y, 360.0);
	
	return;
}

void player_render(node *this)
{
	/* draw node */
	glPushMatrix();
		glTranslated(this->position.x, this->position.y, -this->position.z);
		glRotated(this->rotation.x, 0.0, 1.0, 0.0);
		glScaled(0.1, 0.1, 0.1);
		actor_render(this->node_actor);
	glPopMatrix();
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	return;
}

void player_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			player_init(this);
			break;
		case NR_FREE:
			player_free(this);
			break;
		case NR_COLLIDE:
			player_collision(this);
			break;
		case NR_PLAYER_INPUT:
			player_processinput(this);
			break;
		case NR_PLAYER_CONSTRAINT:
			player_applyconstraints(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			fprintf(stderr, "Routine not implemented for node %d: %d\n", this->id, this->routine_index);
			break;
	}
	
	return;
}

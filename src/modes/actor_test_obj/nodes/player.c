/*
 * player - the player is you!
 */
#include "../nodes.h"

static int orbit_node;
static int orbit_child_index;

void player_init(node *this)
{
	this->node_actor = at_tet_new();
	actor_routine(this->node_actor, AR_INIT);
	
	player_has_orbit = false;
	player_move_forward = 0.0;
	player_move_right = 0.0;
	player_move_up = 0.0;
	player_vertical_vel = 0.0;
	player_vertical_accel = -0.09;
	trigger_jump = false;
	orbit_node = 0;
	orbit_child_index = 0;
	
	return;
}

void player_free(node *this)
{
	node_free(this);
	
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
	vect_component camera_xz = { 0.0, 0.0 };
		
	/* determine current x normal */ 
	veccomp2d_calc(1.0, graph->camera->rotation.x, &camera_xz);
	
	/* motion relative to camera angle */
	if (player_move_forward) {
		this->position.x += player_move_forward * camera_xz.y;
		this->position.z += player_move_forward * camera_xz.x;
		if (player_move_forward > 0.0)
			this->rotation.x = -graph->camera->rotation.x;
		else
			this->rotation.x = 540 - graph->camera->rotation.x;
		player_move_forward = 0.0;
	}
	if (player_move_right) {
		if (this->position.z > graph->camera->position.z) {
			veccomp2d_calc(player_move_right, graph->camera->rotation.x, &camera_xz);
			this->position.x += camera_xz.x;
			this->position.z -= camera_xz.y;
		} else {
			veccomp2d_calc(-player_move_right, graph->camera->rotation.x, &camera_xz);
			this->position.x -= camera_xz.x;
			this->position.z += camera_xz.y;
		}
		if (player_move_right > 0.0)
			this->rotation.x = -graph->camera->rotation.x - 90.0;
		else
			this->rotation.x = -graph->camera->rotation.x + 90.0;
		player_move_right = 0.0;
	}
	
	/* jump */
	if (trigger_jump) {
		player_vertical_vel = 0.5;
		trigger_jump = false;
	}
	
	if (player_has_orbit && orbit_node == 0) {
		player_addorbit(this);
	}
	
}

void player_applyconstraints(node *this)
{
	signed int child;
	vect_component orbit_comps = { 0.0, 0.0 };
	
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
	
	/* vertical accel and velocity */
	player_vertical_vel += player_vertical_accel;
	this->position.y += player_vertical_vel;
	
	/* collision */
	scene_enforceboundingnode(graph, this->id);
	
	/* normalize angles */
	this->rotation.x = fmod(this->rotation.x, 360);
	this->rotation.y = fmod(this->rotation.y, 360);
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

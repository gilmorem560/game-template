/*
 * box - a box you can stand on!
 */
#include "../nodes.h"

void box_init(node *this)
{
	this->node_actor = at_cube_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void box_free(node *this)
{
	node_free(this);
	
	return;
}

void box_collision(node *this)
{
	/* do nothing */
	
	return;
}

void box_applyconstraints(node *this)
{	
	/* normalize angles */
	this->rotation.x = fmod(this->rotation.x, 360);
	this->rotation.y = fmod(this->rotation.y, 360);
}

void box_render(node *this)
{
	/* draw node */
	glPushMatrix();
		glTranslated(this->position.x, this->position.y, -this->position.z);
		glScaled(0.5, 0.5, 0.5);
		actor_render(this->node_actor);
	glPopMatrix();
	
	return;
}

void box_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			box_init(this);
			break;
		case NR_FREE:
			box_free(this);
			break;
		case NR_COLLIDE:
			box_collision(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			fprintf(stderr, "Routine not implemented for node %d: %d\n", this->id, this->routine_index);
			break;
	}
	
	return;
}

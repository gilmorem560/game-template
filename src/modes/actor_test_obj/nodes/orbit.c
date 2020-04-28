/*
 * orbit - a small orbiter, orbiting the player node
 */
#include "../nodes.h"

void orbit_init(node *this)
{
	this->node_actor = at_tet_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void orbit_free(node *this)
{
	node_free(this);
	
	return;
}

void orbit_applyconstraints(node *this)
{	
	/* collision */
	scene_enforceboundingnode(graph, this->id);
	
	/* normalize angles */
	this->rotation.x = fmod(this->rotation.x, 360);
	this->rotation.y = fmod(this->rotation.y, 360);
}

void orbit_render(node *this)
{
	/* draw node */
	glPushMatrix();
		glTranslated(this->position.x, this->position.y, -this->position.z);
		glRotated(this->rotation.x, 0.0, 1.0, 0.0);
		glScaled(0.05, 0.05, 0.05);
		actor_render(this->node_actor);
	glPopMatrix();
	
	return;
}

void orbit_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			orbit_init(this);
			break;
		case NR_FREE:
			orbit_free(this);
			break;
		case NR_ORBIT_CONSTRAINT:
			orbit_applyconstraints(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			fprintf(stderr, "Routine not implemented for node %d: %d\n", this->id, this->routine_index);
			break;
	}
	
	return;
}

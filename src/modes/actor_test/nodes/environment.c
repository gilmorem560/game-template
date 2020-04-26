/*
 * environment - the world environment
 */
#include "../nodes.h"

void environment_init(node *this)
{
	this->node_actor = at_cube_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void environment_free(node *this)
{
	actor_routine(this->node_actor, AR_FREE);
	
	return;
}

void environment_render(node *this)
{
	
		/* draw wall */
		glPushMatrix();
			glTranslated(-2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, -2.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 2.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 2.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(-2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(-2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
		glPopMatrix();
		/* draw floor */
		glPushMatrix();
			glTranslated(-2.0, -4.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
		glPopMatrix();
		/* draw walls */
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
		glPopMatrix();
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, -1.0);
			glTranslated(-2.0, -4.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
		glPopMatrix();
		/* draw ceiling */
		glPushMatrix();
			glRotated(180.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, -2.0);
			at_cube_render(this->node_actor);
			glTranslated(2.0, 0.0, 0.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
			glTranslated(0.0, 0.0, 2.0);
			at_cube_render(this->node_actor);
		glPopMatrix();
		
		return;
}

void environment_routine(node *this)
{
	switch (this->routine_index) {
		case NR_NULL:
			break;
		case NR_INIT:
			environment_init(this);
			break;
		case NR_FREE:
			environment_free(this);
			break;
		default:
			fprintf(stderr, "node %d: undefined routine %d\n", this->id, this->routine_index);
			break;
	}
	
	return;
}

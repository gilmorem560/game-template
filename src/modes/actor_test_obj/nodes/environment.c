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
	node_free(this);
	
	return;
}

void environment_collision(node *this)
{
	unsigned short index;
	unsigned short node;
	collided has_collided = {0, 0, 0};
	
	/* act on previous collisions by object type */
	/* environment likely won't have any, environment is typically root node */
	for (index = 0; index < this->collisions_count; index ++) {
		node = this->collisions[index].id;
		switch (graph->nodes[node]->type) {
		default:
			break;
		}
	}
	node_clearcollisions(this);
	
	/* calculate collisions with children and notify them */
	for (index = 0; index < this->children_count; index++) {
		if (this->children[index]->position.x < -2.9)
			has_collided.x = -1;
		else if (this->children[index]->position.x > 2.9)
			has_collided.x = 1;

		if (this->children[index]->position.y < -2.9)
			has_collided.y = -1;
		else if (this->children[index]->position.y > 2.9)
			has_collided.y = 1;
	
		if (this->children[index]->position.z < -11.0)
			has_collided.z = -1;
		else if (this->children[index]->position.z > -1.1)
			has_collided.z = 1;
		
		node_addcollision(this->children[index], this, has_collided);
		
		has_collided.x = 0;
		has_collided.y = 0;
		has_collided.z = 0;
	}
	
	/* act on collisions */
	/* environment does not react, only informs */
	
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
		case NR_COLLIDE:
			environment_collision(this);
			break;
		default:
			fprintf(stderr, "node %d: undefined routine %d\n", this->id, this->routine_index);
			break;
	}
	
	return;
}

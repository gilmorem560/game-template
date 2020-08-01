/*
 * box - a box you can stand on!
 */
#include "../nodes.h"

bool debug_show_col = false;

void box_init(node *this)
{
	this->node_actor = at_cube_new();
	actor_routine(this->node_actor, AR_INIT);
	#ifndef NDEBUG
	debug_show_col = false;
	#endif /* NDEBUG */
	
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
	unsigned int counter = 0;
	unsigned int counter2 = 0;
	double angle = 0.0;
	double angle2 = 0.0;

	/* draw node */
	glPushMatrix();
		glTranslated(this->position.x, this->position.y, -this->position.z);
		glScaled(0.5, 0.5, 0.5);
		actor_render(this->node_actor);
		if (debug_show_col) {
			glDisable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glColor4d(1.0, 0.0, 0.0, 0.5);
			for (counter2 = 0; counter2 < 4; counter2++) {
				glPushMatrix();
					glRotated(angle2, 0.0, 1.0, 0.0);
					for (counter = 0; counter < 4; counter++) {
						glPushMatrix();
							glRotated(angle, 0.0, 0.0, 1.0);
							glTranslated(0.0, 1.0, -2.0);
							glBegin(GL_QUADS);
								glVertex3d(1.0, 0.0, 1.0);
								glVertex3d(1.0, 0.0, -1.0);
								glVertex3d(-1.0, 0.0, -1.0);
								glVertex3d(-1.0, 0.0, 1.0);
							glEnd();
						glPopMatrix();
						angle += 90.0;
					}
				glPopMatrix();
				angle2 += 90.0;
			}
			angle = 0.0;
			glPushMatrix();
				glRotated(90.0, 1.0, 0.0, 0.0);
				for (counter = 0; counter < 4; counter++) {
					glPushMatrix();
						glRotated(angle, 0.0, 0.0, 1.0);
						glTranslated(0.0, 1.0, -2.0);
						glBegin(GL_QUADS);
							glVertex3d(1.0, 0.0, 1.0);
							glVertex3d(1.0, 0.0, -1.0);
							glVertex3d(-1.0, 0.0, -1.0);
							glVertex3d(-1.0, 0.0, 1.0);
						glEnd();
					glPopMatrix();
					angle += 90.0;
				}
			glPopMatrix();
			angle = 0.0;
			glPushMatrix();
				glRotated(270.0, 1.0, 0.0, 0.0);
				for (counter = 0; counter < 4; counter++) {
					glPushMatrix();
						glRotated(angle, 0.0, 0.0, 1.0);
						glTranslated(0.0, 1.0, -2.0);
						glBegin(GL_QUADS);
							glVertex3d(1.0, 0.0, 1.0);
							glVertex3d(1.0, 0.0, -1.0);
							glVertex3d(-1.0, 0.0, -1.0);
							glVertex3d(-1.0, 0.0, 1.0);
						glEnd();
					glPopMatrix();
					angle += 90.0;
				}
			glPopMatrix();
			glDisable(GL_BLEND);
			glEnable(GL_CULL_FACE);
		}
	glPopMatrix();
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
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

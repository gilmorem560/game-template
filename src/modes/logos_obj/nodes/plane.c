/*
 * plane - the plane that logo elements are placed on
 */
#include "../nodes.h"

void plane_init(node *this)
{
	return;
}

void plane_free(node *this)
{
	return;
}

void plane_collide(node *this)
{
	return;
}

void plane_render(node *this)
{
	return;
}

void plane_routine(node *this)
{
	switch (this->routine_index) {
	case NR_INIT:
		plane_init(this);
		break;
	case NR_FREE:
		plane_free(this);
		break;
	case NR_COLLIDE:
		plane_collide(this);
		break;
	default:
		break;
	}
}

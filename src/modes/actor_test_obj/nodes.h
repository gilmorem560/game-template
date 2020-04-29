/*
 * nodes - a collection of nodes and their methods
 */
#ifndef __NODES_H__
#define __NODES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * give direct access to scene and flow
 * some nodes may take lower level control of the game
*/
#include "../actor_test.h"

/*
 * include necessary actors
 */
#include "actors.h"
	
#define NT_ENVIRONMENT	0
void environment_render(node *this);
void environment_routine(node *this);
static int environment_node;


#define NT_CAMERA		1
void camera_refresh(node *this);
void camera_routine(node *this, node *player);
static int camera_node;
	static bool z_adjusted = false;
	#define CAMERA_DIST_MAX	2.0
	
#define NT_PLAYER		2
void player_render(node *this);
void player_routine(node *this);
	#define	NR_PLAYER_INPUT			3
	#define	NR_PLAYER_CONSTRAINT	4
static int player_node;
	GLdouble player_move_forward;
	GLdouble player_move_right;
	GLdouble player_move_up;
	GLdouble player_vertical_vel;
	GLdouble player_vertical_accel;
	bool player_has_orbit;
	bool trigger_jump;
	
#define NT_ORBIT		3
void orbit_render(node *this);
void orbit_routine(node *this);
	#define NR_ORBIT_CONSTRAINT		3
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __NODES_H__ */

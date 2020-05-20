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
extern void environment_render(node *this);
extern void environment_routine(node *this);
static int environment_node;

#define NT_CAMERA		1
extern void camera_refresh(node *this);
extern void camera_routine(node *this, node *player);
static int camera_node;
	static bool z_adjusted = false;
	#define CAMERA_DIST_MAX	2.0
	
#define NT_PLAYER		2
extern void player_render(node *this);
extern void player_routine(node *this);
	#define	NR_PLAYER_INPUT			3
	#define	NR_PLAYER_CONSTRAINT	4
static int player_node;
	extern GLdouble player_move_forward;
	extern GLdouble player_move_right;
	extern GLdouble player_move_up;
	extern GLdouble player_vertical_vel;
	extern GLdouble player_vertical_accel;
	extern bool player_has_orbit;
	extern bool trigger_jump;
	
#define NT_ORBIT		3
extern void orbit_render(node *this);
extern void orbit_routine(node *this);
	#define NR_ORBIT_CONSTRAINT		3

#define NT_BOX		4
extern void box_render(node *this);
extern void box_routine(node *this);

#define NT_COLLECTIBLE 5
extern void collectible_render(node *this);
extern void collectible_routine(node *this);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __NODES_H__ */

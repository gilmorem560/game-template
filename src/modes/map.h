/*
 * map - render a map with player
 */
#ifndef __MAP_H__
#define __MAP_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* common includes */
#include "modes.h"
/* additional includes */
#include "../graphics/objects/hedrons.h"
	
/* game mode stages */
bool map_init(void);		/* OpenGL init */
bool map_render(void); 		/* OpenGL rendering cycle */
bool map_input(void);       /* handle movement based on key masks */
bool map_routine(void);		/* process mode behavior */
bool map_free(void);		/* OpenGL free */

/* OpenGL lists */
GLint map_actor;

/* properties */
GLdouble actor_x;
GLdouble actor_y;
GLdouble actor_z;
GLdouble actor_angle;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MAP_H__ */

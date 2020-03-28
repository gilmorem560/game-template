/*
 * map - Render a map with player
 */
#ifndef __MAP_H__
#define __MAP_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Common includes */
#include "modes.h"
/* Additional includes */
#include "../graphics/objects/hedrons.h"
	
/* game mode stages */
bool map_init(void);		/* OpenGL init */
bool map_renderframe(void); 	/* OpenGL rendering cycle */
bool map_move(void);        	/* handle movement based on key masks */
bool map_free(void);		/* OpenGL free */

/* assets */
/* void *map_bg_img; */

/* OpenGL lists */
GLint actor;

/* OpenGL textures */
/* GLuint map_bg; */

/* properties */
double actor_x;
double actor_y;
double actor_z;
double actor_angle;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MAP_H__ */

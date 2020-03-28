/*
 * sandbox - sandbox for testing
 */
#ifndef __SANDBOX_H__
#define __SANDBOX_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* Common includes */
#include "modes.h"
/* Additional Includes */
#include "../graphics/objects/prisms.h"

/* game mode stages */
bool sandbox_init(void);		/* OpenGL init */
bool sandbox_renderframe(void);	/* OpenGL rendering */
bool sandbox_move(void);		/* handle movement */
bool sandbox_free(void);		/* OpenGL free */

/* assets */

/* properties */
double angleX;
double angleY;
bool smoothShading;
bool flatShading;
double zoom;
double z_dist;
bool z_pos;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SANDBOX_H__ */

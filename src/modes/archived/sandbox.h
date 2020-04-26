/*
 * sandbox - sandbox for testing
 */
#ifndef __SANDBOX_H__
#define __SANDBOX_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"
/* additional Includes */
#include "../graphics/objects/prisms.h"

/* game mode stages */
bool sandbox_init(void);		/* OpenGL init */
bool sandbox_render(void);	    /* OpenGL rendering */
bool sandbox_input(void);		/* handle movement */
bool sandbox_routine(void);     /* process object routine */
bool sandbox_free(void);		/* OpenGL free */

/* properties */
GLdouble sandbox_angle_x;
GLdouble sandbox_angle_y;
GLdouble sandbox_zoom;
GLdouble sandbox_mid_z;
bool sandbox_shading_smooth;
bool sandbox_mid_pos;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SANDBOX_H__ */

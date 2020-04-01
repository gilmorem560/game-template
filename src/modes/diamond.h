/*
 * diamond - render some diamonds
 */
#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* common includes */
#include "modes.h"
/* additional includes */
#include "../graphics/objects/hedrons.h"
	
/* game mode stages */
bool diamond_init(void);	/* OpenGL init */
bool diamond_render(void);	/* OpenGL rendering cycle */
bool diamond_input(void);   /* handle movement based on key masks */
bool diamond_routine(void);	/* process object routine*/
bool diamond_free(void);	/* OpenGL free */

/* OpenGL lists */
GLint diamond1, diamond2, diamond3, diamond4, diamond5;

/* properties */
int diamond_angle;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __DIAMOND_H__ */

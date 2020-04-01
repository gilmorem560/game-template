/*
 * stage - a single 3D playfield
 */

#ifndef __STAGE_H__
#define __STAGE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"

/* game mode methods */
bool stage_init(void);		/* OpenGL init */
bool stage_render(void);	/* OpenGL rendering */
bool stage_input(void);		/* handle movement */
bool stage_routine(void);   /* process object routine */
bool stage_free(void);		/* OpenGL free */

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __STAGE_H__ */

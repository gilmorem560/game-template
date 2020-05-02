/*
 * titlescreen - full game titlescreen w/ menus
 */
#ifndef __TITLESCREEN_H__
#define __TITLESCREEN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"

/* game mode methods */
bool titlescreen_init(void);		/* scene and system init */
bool titlescreen_render(void);		/* scene rendering */
bool titlescreen_input(void);		/* input handling */
bool titlescreen_routine(void);		/* object processing */
bool titlescreen_free(void);		/* free resources */

/* scene */
scene *titlescreen_graph;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __TITLESCREEN_H__ */

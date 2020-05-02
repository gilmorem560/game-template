/*
 * logos - startup logos
 */
#ifndef __LOGOS_H__
#define __LOGOS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"

/* game mode methods */
bool logos_init(void);		/* scene and system init */
bool logos_render(void);	/* scene rendering */
bool logos_input(void);		/* input handling */
bool logos_routine(void);	/* object processing */
bool logos_free(void);		/* free resources */

/* scene */
scene *logos_graph;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __LOGOS_H__ */

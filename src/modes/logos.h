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
extern bool logos_init(void);		/* scene and system init */
extern bool logos_render(void);	/* scene rendering */
extern bool logos_input(void);		/* input handling */
extern bool logos_routine(void);	/* object processing */
extern bool logos_free(void);		/* free resources */

/* scene */
extern scene *logos_graph;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __LOGOS_H__ */

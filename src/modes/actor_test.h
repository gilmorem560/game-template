/*
 * actor_test - ongoing r&d on scene graphs
 */

#ifndef __ACTOR_TEST_H__
#define __ACTOR_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"

/* game mode methods */
extern bool actor_test_init(void);		/* scene and system init */
extern bool actor_test_render(void);	/* scene rendering */
extern bool actor_test_input(void);	/* input handling */
extern bool actor_test_routine(void);	/* object processing */
extern bool actor_test_free(void);		/* free resources */

/* scene */
extern scene *graph;

/* some global constants */
extern double motion_constant;
extern double gravity_constant;
extern double scale_constant;

/* wrapper input to mode input */
extern int input_mask;
#define IM_UP		1
#define IM_DOWN		2
#define IM_LEFT		4
#define IM_RIGHT	8
#define IM_ACTION1	16
#define IM_ACTION2	32

extern bool show_triangle;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTOR_TEST_H__ */

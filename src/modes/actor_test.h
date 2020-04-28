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
bool actor_test_init(void);		/* scene and system init */
bool actor_test_render(void);	/* scene rendering */
bool actor_test_input(void);	/* input handling */
bool actor_test_routine(void);	/* object processing */
bool actor_test_free(void);		/* free resources */

/* scene */
scene *graph;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTOR_TEST_H__ */

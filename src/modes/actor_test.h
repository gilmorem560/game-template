/*
 * actor_test - a test of scene graphs
 */

#ifndef __ACTOR_TEST_H__
#define __ACTOR_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* common includes */
#include "modes.h"
/* additional objects */
#include "../graphics/objects/scene.h"
/* use vector component calcs */
#include "../util/veccomp.h"

/* game mode methods */
bool actor_test_init(void);		/* OpenGL init */
bool actor_test_render(void);	/* OpenGL rendering */
bool actor_test_input(void);	/* handle movement */
bool actor_test_routine(void);	/* process object routine */
bool actor_test_free(void);		/* OpenGL free */

/* assets */
scene *graph;

/* actor types - modes define actor types */
#define AT_ACTOR_ENVIRONMENT	0
#define	AT_ACTOR_CAMERA			1
#define AT_ACTOR_BLOCK			2

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTOR_TEST_H__ */

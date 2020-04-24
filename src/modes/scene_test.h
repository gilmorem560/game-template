/*
 * scene_test - a test of scene graphs
 */

#ifndef __SCENE_TEST_H__
#define __SCENE_TEST_H__

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
bool scene_test_init(void);		/* OpenGL init */
bool scene_test_render(void);	/* OpenGL rendering */
bool scene_test_input(void);	/* handle movement */
bool scene_test_routine(void);	/* process object routine */
bool scene_test_free(void);		/* OpenGL free */

/* assets */
scene *graph;

/* actor types - modes define actor types */
#define	ST_ACTOR_CAMERA	0

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SCENE_TEST_H__ */

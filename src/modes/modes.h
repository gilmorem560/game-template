/*
 * modes - expanding list of game modes
 */

#ifndef __MODES_H__
#define __MODES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* openGL */
#include "../graphics/contexts/glcontext.h"
/* input */
#include "../input/input.h"
/* basic objects */
#include "../graphics/primitives/prim.h"
/* useful macros */
#include "../util/macros.h"
	
/* game modes */
int game_mode;
#include "diamond.h"
	#define	GM_DIAMONDS		0
#include "map.h"
	#define GM_MAP			1
#include "sandbox.h"
	#define GM_SANDBOX		2
#include "stage.h"
	#define GM_STAGE 		3
#include "scene_test.h"
	#define GM_SCENE_TEST	4
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODES_H__ */

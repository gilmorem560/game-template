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
#include "actor_test.h"
	#define	GM_ACTOR_TEST	0

#ifdef INCLUDE_ARCHIVED_MODES
#include "archived/diamond.h"
	#define GM_DIAMONDS		-1
#include "archived/map.h"
	#define GM_MAP			-2
#include "archived/sandbox.h"
	#define GM_SANDBOX		-3
#include "archived/stage.h"
	#define GM_STAGE 		-4
#include "archived/scene_test.h"
	#define GM_SCENE_TEST	-5
#include "archived/actor_test.h"
	#define GM_ACTOR_TEST	-6
#endif	/* INCLUDE_ARCHIVED_MODES */
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODES_H__ */

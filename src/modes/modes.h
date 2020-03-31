/*
 * modes - expanding list of game modes
 */

#ifndef __MODES_H__
#define __MODES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* OpenGL */
#include "../graphics/contexts/glcontext.h"
/* Input */
#include "../input/input.h"
/* Basic Objects */
#include "../graphics/primitives/prim.h"
/* Debugging Features */
#ifndef NDEBUG
#include <stdio.h>
#include <assert.h>
#endif /* NDEBUG */
	
/* game modes */
int game_mode;
#include "diamond.h"
	#define	GM_DIAMONDS	0
#include "map.h"
	#define GM_MAP		1
#include "sandbox.h"
	#define GM_SANDBOX	2
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODES_H__ */

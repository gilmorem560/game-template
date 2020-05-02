/*
 * modes - configurable list of game modes
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
/* vector calculations */
#include "../graphics/primitives/vect.h"
/* scene graphing */
#include "../scene/scene.h"
/* game mode primitive */
#include "../scene/mode.h"
/* useful macros */
#include "../util/macros.h"

/* defined game modes */
#include "logos.h"
#include "titlescreen.h"
#include "actor_test.h"
#define GM_LOGOS		0
#define	GM_TITLESCREEN	1
#define	GM_ACTOR_TEST	2
#define	MODE_COUNT		3

mode *current_mode;
unsigned int mode_index;
unsigned int mode_index_prev;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODES_H__ */

/*
 * nodes - a collection of nodes and their methods
 */
#ifndef __NODES_H__
#define __NODES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * give direct access to scene and flow
 * some nodes may take lower level control of the game
*/
#include "../logos.h"

/*
 * include necessary actors
 */
#include "actors.h"
	
#define NT_PLANE	0
void plane_render(node *this);
void plane_routine(node *this);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __NODES_H__ */

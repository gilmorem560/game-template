/*
 * actors - actor models for the mode
 */
#ifndef __ACTORS_H__
#define __ACTORS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * give direct access to scene and flow
 * some actors may take lower level control of the game
*/	
#include "../actor_test.h"
	
#define AT_CUBE	0
actor *at_cube_new(void);
void at_cube_render(actor *this);
void at_cube_routine(actor *this);

#define AT_TETRAHEDRON 1
actor *at_tet_new(void);
void at_tet_render(actor *this);
void at_tet_routine(actor *this);

#define AT_TRIANGLE 2
actor *at_triangle_new(void);
void at_triangle_render(actor *this);
void at_triangle_routine(actor *this);

#define AT_PERSON 3
actor *at_person_new(void);
void at_person_render(actor *this);
void at_person_routine(actor *this);
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ACTORS_H__ */

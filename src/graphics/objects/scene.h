 /*
  * scene - a primitive scene graph
  */
#ifndef __SCENE_H__
#define __SCENE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* include GL for types */
#include "../contexts/glcontext.h"
	
enum projection_type {
	PROJECTION_ORTHAGONAL
	,PROJECTION_FRUSTUM
};

typedef struct node {
	GLdouble *vertex_array;
	GLdouble *normal_array;
	GLdouble *color_array;
	GLubyte *vao_indicies;
	void *children;
	unsigned int children_count;
} node;
	
typedef struct scene {
	GLdouble *prj;
	char prj_type;
	node *root_node;
} scene;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __SCENE_H__ */

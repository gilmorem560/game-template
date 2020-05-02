/*
 * logos - startup logos
 */ 
#include "logos.h"
#include "logos_obj/nodes.h"

static point3d node_positions[] = {{0.0, 0.0, 0.0}};
static point3d node_angles[] = {{0.0, 0.0, 0.0}};
static short plane_node;
static signed long countdown = 320;

/* 
 * init - scene and system init 
 */
bool logos_init(void)
{
	/* create graph */
	logos_graph = scene_new();
	
	/* scene projection */
	scene_projection_new(logos_graph, PROJECTION_ORTHAGONAL, current_ratio, 1.0, -1.0, 1.0);

	/* setup collision bounding box */
	logos_graph->bounding_box[0] = logos_graph->prj[0];
	logos_graph->bounding_box[1] = logos_graph->prj[1];
	logos_graph->bounding_box[2] = logos_graph->prj[2];
	logos_graph->bounding_box[3] = logos_graph->prj[3];
	logos_graph->bounding_box[4] = logos_graph->prj[4];
	logos_graph->bounding_box[5] = logos_graph->prj[5];
	
	/* create node collection */
	
	/* create node 00 - plane */
	plane_node = scene_addnode(logos_graph, NT_PLANE, NULL, plane_routine);
	scene_positionnode(logos_graph, plane_node, node_positions[plane_node]);
	scene_rotatenode(logos_graph, plane_node, node_angles[plane_node]);
	
	/* --- OpenGL Init --- */
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_FOG);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* color settings */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	/* setup culling */
	glCullFace(GL_BACK);
	
	/* setup projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	switch(logos_graph->prj_type) {
	case PROJECTION_ORTHAGONAL:
		glOrtho(logos_graph->prj[0], logos_graph->prj[1], logos_graph->prj[2], logos_graph->prj[3], logos_graph->prj[4], logos_graph->prj[5]);
		break;
	case PROJECTION_FRUSTUM:
		glFrustum(logos_graph->prj[0], logos_graph->prj[1], logos_graph->prj[2], logos_graph->prj[3], logos_graph->prj[4], logos_graph->prj[5]);
		break;
	default:
		fprintf(stderr, "Projection mode %d not supported.\n", graph->prj_type);
		return false;
		break;
	}
	
	return true;
}

/*
 * render - scene rendering
 */
bool logos_render(void)
{
	unsigned int node_index;
	
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT);
	
	/* update projection if viewport changes shape */
	if (logos_graph->prj[1] != current_ratio) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		logos_graph->prj[0] = -current_ratio;
		logos_graph->prj[1] = current_ratio;
		glOrtho(logos_graph->prj[0], logos_graph->prj[1], logos_graph->prj[2], logos_graph->prj[3], logos_graph->prj[4], logos_graph->prj[5]);
	}
	
	/* begin rendering */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	glPopMatrix();
	
	glFlush();
	
	drawframe();
	
	return true;
}

/*
 * input - input handling
 */
bool logos_input(void)
{
	return true;
}

/*
 * routine - object processing
 */
bool logos_routine(void)
{
	if (--countdown <= 0) {
		mode_index = GM_ACTOR_TEST;
	}
	
	return true;
}

/*
 * free - free resources
 */
bool logos_free(void)
{
	scene_free(logos_graph);
	return true;
}

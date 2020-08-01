/*
 * actor_test - a test of scene graphs
 */
#include "actor_test.h"
#include "actor_test_obj/nodes.h"			

/* scene */
scene *graph;

typedef struct graph_table {
	signed short type;
	void (*render)(node *);
	void (*routine)(node *);
} graph_table ;

/* some global constants */
double motion_constant;
double gravity_constant;
double scale_constant;

/* wrapper input to mode input */
int input_mask;

/* trigger to display triangle in HUD */
bool show_triangle;
								  
static double bounding_box[] = {-2.9, 2.9, -2.9, 2.9, -11.0, -1.1};
static GLfloat fog_color[] = { 0.3f, 0.3f, 0.3f, 1.0f };
static point3d node_positions[] = {
		{0.0,0.0,0.0}		/* environment */
		,{0.0,0.0,-2.0}		/* camera */
		,{0.0,0.0,-5.0}		/* player */
		,{0.0,-2.5,-6.0}	/* box 1 */
		,{0.0,-1.5,-7.0}	/* box 2 */
		,{0.0,-0.5,-8.0}	/* box 3 */
		,{0.0,-0.5,-11.0}	/* box 4 */
		,{0.0,1.5,-11.0}	/* collectible */
		,{3.0,-2.5,-6.0}	/* box 5 */
};
static point3d node_angles[] = {
		{0.0,0.0,0.0}		/* environment */
		,{0.0,0.0,0.0}		/* camera */
		,{0.0,0.0,0.0}		/* player */
		,{0.0,0.0,0.0}		/* box 1 */
		,{0.0,0.0,0.0}		/* box 2 */
		,{0.0,0.0,0.0}		/* box 3 */
		,{0.0,0.0,0.0}		/* box 4 */
		,{0.0,0.0,0.0}		/* collectible */
		,{0.0,0.0,0.0}		/* box 5 */
};

static graph_table scene_table[] = {
		{NT_ENVIRONMENT, &environment_render, &environment_routine}
		,{NT_CAMERA, NULL, NULL}
		,{NT_PLAYER, &player_render, &player_routine}
		,{NT_BOX, &box_render, &box_routine}
		,{NT_BOX, &box_render, &box_routine}
		,{NT_BOX, &box_render, &box_routine}
		,{NT_BOX,  &box_render, &box_routine}
		,{NT_COLLECTIBLE, &collectible_render, &collectible_routine}
		,{NT_BOX, &box_render, &box_routine}
};

#define NODE_COUNT 9

/*
 * actor_test_init - OpenGL init
 */
bool actor_test_init(void)
{
	unsigned char index;
	unsigned short node_id;
	#ifndef NDEBUG
	printf("actor_test: init\n");
	#endif /* NDEBUG */
	
	/* --- scene init --- */
	
	input_mask = 0;
	motion_constant = 0.1;		/* constants for our world */
	gravity_constant = -0.09;	/* TODO: make meta-data of the environment node */
	scale_constant = 0.1;
	show_triangle = false;
	
	/* create graph */
	graph = scene_new();
	
	/* scene projection */
	scene_projection_new(graph, PROJECTION_FRUSTUM, scale_constant * current_ratio, scale_constant, scale_constant, 50.0);

	/* setup collision bounding box */
	graph->bounding_box[0] = bounding_box[0];
	graph->bounding_box[1] = bounding_box[1];
	graph->bounding_box[2] = bounding_box[2];
	graph->bounding_box[3] = bounding_box[3];
	graph->bounding_box[4] = bounding_box[4];
	graph->bounding_box[5] = bounding_box[5];
	
	/* create node collection */
	for (index = 0; index < NODE_COUNT; index++) {
		node_id = scene_addnode(graph, scene_table[index].type, scene_table[index].render, scene_table[index].routine);
		scene_positionnode(graph, node_id, node_positions[index]);
		scene_rotatenode(graph, node_id, node_angles[index]);
		if (node_id != 0)
			scene_setchildnode(graph, 0, node_id);	/* currently all initial nodes instantiated as children of environment, if nodes have children they will manage */

		/* assign special nodes */
		switch (scene_table[index].type) {
		case NT_ENVIRONMENT:
			graph->environment = graph->nodes[node_id];
			break;
		case NT_CAMERA:
			graph->camera = graph->nodes[node_id];
			break;
		case NT_PLAYER:
			graph->player = graph->nodes[node_id];
			break;
		default:
			break;
		}
	}
	
	/* assign environment as our root node */
	graph->root_node = graph->nodes[0];
	
	/* --- OpenGL Init --- */
	
	/* TODO: Create OpenGL "modes" that control all parameter switching */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_FOG);
	glDisable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* color settings */
	glClearColor(fog_color[0], fog_color[1], fog_color[2], fog_color[3]);
	glShadeModel(GL_SMOOTH);
	
	/* setup culling */
	glCullFace(GL_BACK);
	
	/* fog setup */
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_DENSITY, 0.45f);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 10.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	/* setup projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	switch(graph->prj_type) {
	case PROJECTION_ORTHAGONAL:
		glOrtho(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);
		break;
	case PROJECTION_FRUSTUM:
		glFrustum(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);
		break;
	default:
		fprintf(stderr, "Projection mode %d not supported.\n", graph->prj_type);
		return false;
		break;
	}
	
	return true;
}

/*
 * actor_test_render - OpenGL rendering
 */
bool actor_test_render(void)
{
	unsigned int node_index;
	
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* update projection if viewport changes shape */
	if (graph->prj[1] != (current_ratio * scale_constant)) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		graph->prj[0] = -(current_ratio * scale_constant);
		graph->prj[1] = (current_ratio * scale_constant);
		glFrustum(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);
	}

	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/* projection matrix */
	glPushMatrix();
		/* begin rendering in world space */
		glPushMatrix();
		
			/* perform camera transformation */
			camera_refresh(graph->camera);
		
			/* step through nodes render functions */
			/* todo: create a "render space" flag for nodes */
			for (node_index = 0; node_index < graph->node_count; node_index++) {
				node_render(graph->nodes[node_index]);
			}
		
		/* end rendering in world space */
		glPopMatrix();
	glPopMatrix();
	
	/* test hud elements */
	if (show_triangle) {
		glDisable(GL_DEPTH_TEST);

		glBegin(GL_TRIANGLES);
			glColor4d(1.0, 1.0, 0.0, 0.0);
			glVertex3d(-0.75, -0.5, -1.0);
			glVertex3d(-0.95, -0.95, -1.0);
			glVertex3d(-0.55, -0.95, -1.0);
		glEnd();

		glEnable(GL_DEPTH_TEST);
	}
	
	/* flush */
	glFlush();

	/* display */
	drawframe();
	
	return true;
}

/*
 * actor_test_input - handle movement
 */
bool actor_test_input(void)
{	
	/* movement */
	/* w - up */	if ((key_pressed & KEY_W) | (key_held & KEY_W)) input_mask |= IM_UP;
	/* s - down */	if ((key_pressed & KEY_S) | (key_held & KEY_S)) input_mask |= IM_DOWN;
	/* a - left */	if ((key_pressed & KEY_A) | (key_held & KEY_A)) input_mask |= IM_LEFT;
	/* d - right */ if ((key_pressed & KEY_D) | (key_held & KEY_D)) input_mask |= IM_RIGHT;
	
	/* actions */
	/* e - tap action 1 */	if (key_pressed & KEY_SPACE) input_mask |= IM_ACTION1;
	/* c - any action 2 */	if (key_held & KEY_C) input_mask |= IM_ACTION2;
	
	/* system */
	/* q - quit */	if (key_held & KEY_Q) quit = true;
	
	#ifdef HAVE_LIBEVDEV_LIBEVDEV_H
	/* start - quit */		if (pad_pressed & (1 << PAD_START)) quit = true;
	#endif /* HAVE_LIBEVDEV_LIBEVDEV_H */

	key_pressed = 0;
	
	return true;
}

/*
 * actor_test_routine -  process object routine 
 */
bool actor_test_routine(void)
{
	/* handle the player's input and apply constraints to result */
	node_routine(graph->player, NR_PLAYER_INPUT);
	node_routine(graph->player, NR_PLAYER_CONSTRAINT);
	
	/* process the collision state of the scene */
	node_routine(graph->root_node, NR_COLLIDE);

	/* enforce camera that follows the player */
	/* camera is always after the player */
	camera_routine(graph->camera, graph->player);
	
	return true;
}

/*
 * actor_test_free - OpenGL free
 */
bool actor_test_free(void)
{
	#ifndef NDEBUG
	printf("actor_test: free\n");
	#endif /* NDEBUG */

	scene_free(graph);
	
	return true;
}


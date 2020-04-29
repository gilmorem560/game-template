/*
 * actor_test - a test of scene graphs
 */
#include "actor_test.h"
#include "actor_test_obj/nodes.h"								  
								  
static double bounding_box[] = {-2.9, 2.9, -2.9, 2.9, -11.0, -1.1};
static GLfloat fog_color[] = { 0.3f, 0.3f, 0.3f, 1.0f };
static point3d node_positions[] = {{0.0,0.0,0.0},{0.0,0.0,-5.0},{0.0,0.0,-2.0}};
static point3d node_angles[] = {{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}};

/*
 * actor_test_init - OpenGL init
 */
bool actor_test_init(void)
{
	#ifndef NDEBUG
	printf("actor_test: init\n");
	#endif /* NDEBUG */
	
	/* --- scene init --- */
	
	input_mask = 0;
	motion_constant = 0.1;		/* constants for our world */
	gravity_constant = -0.09;	/* TODO: make meta-data of the environment node */
	scale_constant = 0.1;
	
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
	
	/* create node 00 - environment */
	environment_node = scene_addnode(graph, NT_ENVIRONMENT, environment_render, environment_routine);
	scene_positionnode(graph, environment_node, node_positions[environment_node]);
	scene_rotatenode(graph, environment_node, node_angles[environment_node]);
	
	/* create node 01 - camera */
	camera_node = scene_addnode(graph, NT_CAMERA, NULL, NULL);
	scene_positionnode(graph, camera_node, node_positions[camera_node]);
	scene_rotatenode(graph, camera_node, node_angles[camera_node]);
	scene_setchildnode(graph, environment_node, camera_node);
		
	/* create node 02 - player box */
	player_node = scene_addnode(graph, NT_PLAYER, player_render, player_routine);
	scene_positionnode(graph, player_node, node_positions[player_node]);
	scene_rotatenode(graph, player_node, node_angles[player_node]);
	scene_setchildnode(graph, environment_node, player_node);
	
	/* assign environment */
	graph->environment = graph->nodes[environment_node];
	
	/* assign camera */
	graph->camera = graph->nodes[camera_node];
	
	/* assign player */
	graph->player = graph->nodes[player_node];
	
	/* assign environment as our root node */
	graph->root_node = graph->environment;
	
	/* --- OpenGL Init --- */
	
	/* TODO: Create OpenGL "modes" that control all parameter switching */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_FOG);
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
		
		/* begin rendering in unadjusted projection space */
		glPushMatrix();
		
		/* end rendering in projection space */
		glPopMatrix();
	glPopMatrix();
	
	/* push to a frame */
	glFlush();
	
	/* orthagonal planes */
	glOrtho(-current_ratio, current_ratio, -1.0, 1.0, -1.0, 1.0);
	glPushMatrix();
		/* begin rendering behind world space */
		glPushMatrix();
		
		/* end rendering behind world space */
		glPopMatrix();
		
		/* begin rendering on top of projection space */
		glPushMatrix();
		
		/* end rendering on top of projection space */
		glPopMatrix();
	glPopMatrix();
	
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
	/* w - up */	if (key_pressed & KEY_W || key_held & KEY_W) input_mask |= IM_UP;
	/* s - down */	if (key_pressed & KEY_S || key_held & KEY_S) input_mask |= IM_DOWN;
	/* a - left */	if (key_pressed & KEY_A || key_held & KEY_A) input_mask |= IM_LEFT;
	/* d - right */ if (key_pressed & KEY_D || key_held & KEY_D) input_mask |= IM_RIGHT;
	
	/* actions */
	/* e - tap action 1 */	if (key_pressed & KEY_E) input_mask |= IM_ACTION1;
	/* c - any action 2 */	if (key_held & KEY_C) input_mask |= IM_ACTION2;
	
	/* system */
	/* q - quit */	if (key_held & KEY_Q) quit = true;

	#ifndef NDEBUG	
	debug_pollkeys(key_held);
	#endif /* NDEBUG */
	
	key_pressed = 0;
	
	return true;
}

/*
 * actor_test_routine -  process object routine 
 */
bool actor_test_routine(void)
{
	node_routine(graph->player, NR_PLAYER_INPUT);
	node_routine(graph->player, NR_PLAYER_CONSTRAINT);
	
	node_routine(graph->root_node, NR_COLLIDE);
	node_routine(graph->player, NR_COLLIDE);

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
	int node_count;
	#ifndef NDEBUG
	printf("actor_test: free\n");
	#endif /* NDEBUG */

	scene_free(graph);
	
	return true;
}


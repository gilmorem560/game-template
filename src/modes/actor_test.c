/*
 * actor_test - a test of scene graphs
 */
#include "actor_test.h"

static GLdouble vertex_array[24] = { -1.0,  1.0, 1.0
									,-1.0, -1.0, 1.0
									, 1.0, -1.0, 1.0
									, 1.0,  1.0, 1.0
									, 1.0,  1.0, -1.0
									, 1.0, -1.0, -1.0
									,-1.0, -1.0, -1.0
									,-1.0,  1.0, -1.0 };
							 
static GLdouble normal_array[24] = { -1.0,  1.0,  1.0
									,-1.0, -1.0,  1.0
									, 1.0, -1.0,  1.0
									, 1.0,  1.0,  1.0
									, 1.0,  1.0, -1.0
									, 1.0, -1.0, -1.0
									,-1.0, -1.0, -1.0
									,-1.0,  1.0, -1.0 };
							 
static GLdouble color_array[24] = { 1.0, 0.0, 0.0
								   ,0.0, 1.0, 0.0
								   ,0.0, 0.0, 1.0
								   ,1.0, 1.0, 0.0
								   ,0.0, 1.0, 1.0
								   ,1.0, 0.0, 1.0
								   ,1.0, 1.0, 0.5
								   ,0.5, 1.0, 1.0 };
							
static GLubyte vao_indicies[24] = { 0, 1, 2, 3
								  ,3, 2, 5, 4
								  ,4, 5, 6, 7
								  ,7, 6, 1, 0
								  ,7, 0, 3, 4
								  ,1, 6, 5, 2 };
								  
								  
static GLfloat fog_color[] = { 0.3f, 0.3f, 0.3f, 1.0f };
				
/* static nodes */
static signed int environment_node;

static signed int camera_node;
	static GLdouble camera_view_x;
	static GLdouble camera_view_y;
	static veccomp2d camera_view_xz;
	static bool z_adjusted = false;

static signed int player_node;
	static GLdouble player_move_forward;
	static GLdouble player_move_right;
	static GLdouble player_move_up;
	static GLdouble player_vertical_vel;
	static GLdouble player_vertical_accel;
	static veccomp2d forward_xz;
	static veccomp2d right_xz;
	static veccomp2d up_xz;
	static bool trigger_jump;
	
static double motion_constant = 0.1;
static double gravity_constant = -0.09;

/*
 * actor_test_init - OpenGL init
 */
bool actor_test_init(void)
{
	#ifndef NDEBUG
	printf("actor_test: init\n");
	#endif /* NDEBUG */
	
	/* --- scene init --- */
	
	/* create graph */
	graph = malloc(sizeof (scene));
	graph->nodes = NULL;
	graph->node_count = 0;
	
	/* scene projection */
	scene_projection_new(graph, PROJECTION_FRUSTUM, current_ratio, 1.0, 1.0, 30.0);

	/* setup collision bounding box */
	graph->bounding_box[0] = -2.9;
	graph->bounding_box[1] = 2.9;
	graph->bounding_box[2] = -2.9;
	graph->bounding_box[3] = 2.9;
	graph->bounding_box[4] = -6.0;
	graph->bounding_box[5] = -1.1;
	
	/* create node collection */
	
	/* create node 00 - environment */
	environment_node = scene_addnode(graph, AT_ACTOR_ENVIRONMENT, false, ACTOR_ROUTINE_NULL, NULL);
	scene_positionnode(graph, environment_node, 0.0, 0.0, 0.0);
	scene_skinnode(graph, environment_node, vertex_array, normal_array, color_array, vao_indicies);
	scene_positionenv(graph, 0.0, 0.0, 0.0);
	
	/* create node 01 - camera */
	camera_node = scene_addnode(graph, AT_ACTOR_CAMERA, false, ACTOR_ROUTINE_NULL, NULL);
	scene_positionnode(graph, camera_node, 0.0, 0.0, -5.0);
	scene_setchildnode(graph, environment_node, camera_node);
		
	/* create node 02 - player box */
	player_node = scene_addnode(graph, AT_ACTOR_BLOCK, false, ACTOR_ROUTINE_NULL, NULL);
	scene_positionnode(graph, player_node, 0.0, 0.0, -2.0);
	scene_skinnode(graph, player_node, vertex_array, normal_array, color_array, vao_indicies);
	scene_setchildnode(graph, environment_node, player_node);
	
	/* assign environment */
	graph->environment = graph->nodes[environment_node];
	
	/* assign camera */
	graph->camera = graph->nodes[camera_node];
	
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
	
	/* set initial camera angle */
	camera_view_x = 0.0;
	camera_view_y = 0.0;
	veccomp2d_calc(1.0, camera_view_x, &camera_view_xz);
	
	/* set player properties */
	player_move_forward = 0.0;
	player_move_right = 0.0;
	player_move_up = 0.0;
	player_vertical_vel = 0.0;
	player_vertical_accel = gravity_constant;
	trigger_jump = false;
	
	return true;
}

/*
 * actor_test_render - OpenGL rendering
 */
bool actor_test_render(void)
{
	int i = 0, j = 0;
	
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* update projection if viewport changes shape */
	if (graph->prj[1] != current_ratio) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		graph->prj[0] = -current_ratio;
		graph->prj[1] = current_ratio;
		glFrustum(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);
	}

	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
		/* perform camera transformation */
		glRotated(camera_view_x, 0.0, 1.0, 0.0);
		glRotated(camera_view_y, camera_view_xz.x, 0.0, camera_view_xz.y);
		glTranslated(graph->camera->position[0], graph->camera->position[1], graph->camera->position[2]);
		
		/* bind environment arrays */
		glVertexPointer(3, GL_DOUBLE, 0, graph->environment->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, graph->environment->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, graph->environment->color_array);
		
		/* draw wall */
		glPushMatrix();
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, -2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
		glPopMatrix();
		/* draw floor */
		glPushMatrix();
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
		glPopMatrix();
		/* draw walls */
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
		glPopMatrix();
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, -1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
		glPopMatrix();
		/* draw ceiling */
		glPushMatrix();
			glRotated(180.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->environment->vao_indicies);
		glPopMatrix();
				
		/* bind player arrays */
		glVertexPointer(3, GL_DOUBLE, 0, graph->nodes[player_node]->vertex_array);
		glNormalPointer(GL_DOUBLE, 0, graph->nodes[player_node]->normal_array);
		glColorPointer(3, GL_DOUBLE, 0, graph->nodes[player_node]->color_array);
		
		/* draw actor */
		glPushMatrix();
			glTranslated(graph->nodes[player_node]->position[0], graph->nodes[player_node]->position[1], -graph->nodes[player_node]->position[2]);
			glScaled(0.1, 0.1, 0.1);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->nodes[player_node]->vao_indicies);
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
	/* w - forward */	if (key & KEY_W) player_move_forward += motion_constant;
	/* s - back */		if (key & KEY_S) player_move_forward -= motion_constant;
	/* a - left */		if (key & KEY_A) player_move_right += motion_constant;
	/* d - right */ 	if (key & KEY_D) player_move_right -= motion_constant;
	
	/* r - up */		if (key & KEY_R) player_move_up -= motion_constant;
	/* f - down */		if (key & KEY_F) player_move_up += motion_constant;
	
	/* e - jump */		if (key & KEY_E) { trigger_jump = true; }

	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (KEY_ISNUM(key) && !(key & KEY_6)) {
		actor_test_free();
		switch (key) {
			case KEY_1:
				diamond_init();
				game_mode = GM_DIAMONDS;
				break;
			case KEY_2:
				map_init();
				game_mode = GM_MAP;
				break;
			case KEY_3:
				sandbox_init();
				game_mode = GM_SANDBOX;
				break;
			case KEY_4:
				stage_init();
				game_mode = GM_STAGE;
				break;
			case KEY_5:
				scene_test_init();
				game_mode = GM_SCENE_TEST;
				break;
			default:
				quit = true;
				break;
		}
	}
	
	debug_pollkeys(key);
	#endif /* NDEBUG */
	
	return true;
}

/*
 * actor_test_routine -  process object routine 
 */
bool actor_test_routine(void)
{
	double camera_dist_x, camera_dist_y, camera_dist_z;
	
	/* player */
	/* motion */
	if (player_move_forward) {
		graph->nodes[player_node]->position[2] += player_move_forward;
		player_move_forward = 0.0;
	}
	if (player_move_right) {
		graph->nodes[player_node]->position[0] += player_move_right;
		player_move_right = 0.0;
	}
	/* jump */
	if (trigger_jump) {
		player_vertical_vel = -0.5;
		trigger_jump = false;
	}
	/* vertical accel and velocity */
	player_vertical_vel -= player_vertical_accel;
	graph->nodes[player_node]->position[1] += player_vertical_vel;
	/* collision */
	scene_enforceboundingnode(graph, player_node);
	
	/* camera */
	/* move camera */
	
	/* position camera */
	camera_dist_x = graph->camera->position[0] - graph->nodes[player_node]->position[0];
	camera_dist_y = graph->camera->position[1] - graph->nodes[player_node]->position[1];
	camera_dist_z = graph->camera->position[2] - graph->nodes[player_node]->position[2];
	camera_view_x = vecang2d_calc(camera_dist_x, camera_dist_z);
	camera_view_y = vecang2d_calc(camera_dist_y, camera_dist_z);
	
	/* normalize angles */
	camera_view_x = fmod(camera_view_x, 360);
	camera_view_y = fmod(camera_view_y, 360);
	
	/* calculate y rotation vector */
	veccomp2d_calc(1.0, camera_view_x, &camera_view_xz);
	
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

	for (node_count = 0; node_count < graph->node_count; node_count++) {
		free(graph->nodes[node_count]->actor_entry.actor_obj);
		free(graph->nodes[node_count]->children);
		free(graph->nodes[node_count]);
	}
	free(graph->nodes);
	free(graph);
	
	return true;
}


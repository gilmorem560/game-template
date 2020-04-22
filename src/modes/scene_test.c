/*
 * scene_test - a test of scene graphs
 */
#include "scene_test.h"

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
				
static GLdouble forward;
static GLdouble right;
static GLdouble xpos;
static GLdouble ypos;
static GLdouble zpos;
static GLdouble view_x;
static GLdouble view_y;

static veccomp2d view_xz;
static veccomp2d forward_xz;
static veccomp2d right_xz;

static bool z_adjusted = false;

/*
 * scene_test_init - OpenGL init
 */
bool scene_test_init(void)
{
	#ifndef NDEBUG
	printf("scene_test: init\n");
	#endif /* NDEBUG */
	
	/* --- scene init --- */
	
	/* create graph */
	graph = malloc(sizeof (scene));
	graph->node_count = 0;
	
	/* create environment */
	graph->root_environment = malloc(sizeof (environment));
	graph->root_environment->actor_entry.id = SCENE_ACTOR_NULL;
	graph->root_environment->children = NULL;
	graph->root_environment->children_count = 0;
	
	/* create camera */
	graph->camera = malloc(sizeof (actor));
		graph->camera->type = ST_ACTOR_CAMERA;
		graph->camera->type_router = false;
		graph->camera->routine = ACTOR_ROUTINE_NULL;
		graph->camera->router = NULL;
	
	/* create root node - camera */
	graph->root_node = malloc(sizeof (node));
		graph->root_node->actor_entry.id = 0;
		graph->root_node->actor_entry.actor_obj = graph->camera;	/* camera is root node & object */
		
	/* register root node in node collection */
	graph->nodes = graph->root_node;
	graph->node_count++;
		
	/* scene projection */
	scene_projection_new(graph, PROJECTION_FRUSTUM, current_ratio, 1.0, 1.0, 11.0);
	
	/* setup camera properties */
	xpos = 0.0;
	ypos = 0.0;
	zpos = -((graph->prj[4] + graph->prj[5]) / 2);
	view_x = 0.0;
	view_y = 0.0;
	forward = 0.0;
	right = 0.0;
	view_xz.x = 0.0;
	view_xz.y = 0.0;
	
	/* scene geometry */
	graph->root_environment->vertex_array = vertex_array;
	graph->root_environment->normal_array = normal_array;
	graph->root_environment->color_array = color_array;
	graph->root_environment->vao_indicies = vao_indicies;
	
	if (!z_adjusted) {
		graph->root_environment->vertex_array[2] += zpos;
		graph->root_environment->vertex_array[5] += zpos;
		graph->root_environment->vertex_array[8] += zpos;
		graph->root_environment->vertex_array[11] += zpos;
		graph->root_environment->vertex_array[14] += zpos;
		graph->root_environment->vertex_array[17] += zpos;
		graph->root_environment->vertex_array[20] += zpos;
		graph->root_environment->vertex_array[23] += zpos;
		z_adjusted = true;
	}
	
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

	glVertexPointer(3, GL_DOUBLE, 0, graph->root_environment->vertex_array);
	glNormalPointer(GL_DOUBLE, 0, graph->root_environment->normal_array);
	glColorPointer(3, GL_DOUBLE, 0, graph->root_environment->color_array);
	
	return true;
}

/*
 * scene_test_render - OpenGL rendering
 */
bool scene_test_render(void)
{
	int i = 0, j = 0;
	
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* update projection if viewport changes shape */
	//if (graph->prj[1] != current_ratio) {
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	graph->prj[0] = -current_ratio;
	//	graph->prj[1] = current_ratio;
	//	glFrustum(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);
	//}

	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
		glRotated(view_x, 0.0, 1.0, 0.0);
		glRotated(view_y, view_xz.x, 0.0, view_xz.y);
		glTranslated(xpos, ypos, zpos + ((graph->prj[4] + graph->prj[5]) / 2));
		/* draw wall */
		glPushMatrix();
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, -2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
		glPopMatrix();
		/* draw floor */
		glPushMatrix();
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
		glPopMatrix();
		/* draw walls */
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
		glPopMatrix();
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, -1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
		glPopMatrix();
		/* draw ceiling */
		glPushMatrix();
			glRotated(180.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_environment->vao_indicies);
		glPopMatrix();
	glPopMatrix();
	
	/* flush */
	glFlush();

	/* display */
	drawframe();
	
	return true;
}

/*
 * scene_test_input - handle movement
 */
bool scene_test_input(void)
{	
	/* movement */
	/* w - up */	if (key & KEY_W) forward += 0.3;
	/* s - down */	if (key & KEY_S) forward -= 0.3;
	/* a - left */	if (key & KEY_A) right += 0.3;
	/* d - right */ if (key & KEY_D) right -= 0.3;
	
	/* mouse controls view angle */
	if (mouse_moved_x) view_x += 2.0 * (mouse_x_positive ? 1.0 : -1.0);
	if (mouse_moved_y) view_y += 2.0 * (mouse_y_positive ? 1.0 : -1.0);

	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (KEY_ISNUM(key) && !(key & KEY_5)) {
		scene_test_free();
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
 * scene_test_routine -  process object routine 
 */
bool scene_test_routine(void)
{
	/* normalize angles */
	view_x = fmod(view_x, 360);
	view_y = fmod(view_y, 360);
	
	/* calculate y rotation vector */
	veccomp2d_calc(1.0, view_x, &view_xz);
	
	/* calculation motion vector */
	if (forward) {
		veccomp2d_calc(forward, view_x, &forward_xz);
		xpos -= forward_xz.y;
		zpos += forward_xz.x;
		forward = 0.0;
	}
	if (right) {
		veccomp2d_calc(right, view_x, &right_xz);
		xpos += right_xz.x;
		zpos += right_xz.y;
		right = 0.0;
	}
	
	
	
	return true;
}

/*
 * scene_test_free - OpenGL free
 */
bool scene_test_free(void)
{
	#ifndef NDEBUG
	printf("scene_test: free\n");
	#endif /* NDEBUG */

	/* TODO: Solve heap corruption issue */
	free(graph->root_node);
	free(graph->camera);
	free(graph->root_environment);
	free(graph->prj);
	free(graph);
	
	return true;
}


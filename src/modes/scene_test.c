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
							
static GLdouble xpos;
static GLdouble ypos;
static GLdouble zpos;
static GLdouble view_x;
static GLdouble view_y;

/*
 * scene_test_init - OpenGL init
 */
bool scene_test_init(void)
{
	#ifndef NDEBUG
	printf("scene_test: init\n");
	#endif /* NDEBUG */
	
	/* TODO: Create OpenGL "modes" that control all parameter switching */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_FOG);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* set background color */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	/* black background */
	
	/* setup culling */
	glCullFace(GL_BACK);
	
	glShadeModel(GL_SMOOTH);
	
	/* setup projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	/* setup scene graph */
	graph = (scene *) malloc(sizeof (graph));
	graph->prj = (GLdouble *) malloc(6 * sizeof (GLdouble));
	graph->root_node = (node *) malloc(sizeof (node));
	graph->root_node->children = NULL;
	graph->root_node->children_count = 0;

	/* TODO: Create method in scene for setting up scene projection based on properties */
	/* scene projection */
	graph->prj[0] = -1.0;
	graph->prj[1] = 1.0;
	graph->prj[2] = -1.0;
	graph->prj[3] = 1.0;
	graph->prj[4] = 5.0;
	graph->prj[5] = 70.0;
	graph->prj_type = PROJECTION_FRUSTUM;
	
	xpos = 0.0;
	ypos = 0.0;
	zpos = -((graph->prj[4] + graph->prj[5]) / 2);
	view_x = 0.0;
	view_y = 0.0;
	
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
	
	/* scene geometry */
	graph->root_node->vertex_array = vertex_array;
	graph->root_node->normal_array = normal_array;
	graph->root_node->color_array = color_array;
	graph->root_node->vao_indicies = vao_indicies;
	
	graph->root_node->vertex_array[2] += zpos;
	graph->root_node->vertex_array[5] += zpos;
	graph->root_node->vertex_array[8] += zpos;
	graph->root_node->vertex_array[11] += zpos;
	graph->root_node->vertex_array[14] += zpos;
	graph->root_node->vertex_array[17] += zpos;
	graph->root_node->vertex_array[20] += zpos;
	graph->root_node->vertex_array[23] += zpos;

	glVertexPointer(3, GL_DOUBLE, 0, graph->root_node->vertex_array);
	glNormalPointer(GL_DOUBLE, 0, graph->root_node->normal_array);
	glColorPointer(3, GL_DOUBLE, 0, graph->root_node->color_array);
	
	return true;
}

/*
 * scene_test_render - OpenGL rendering
 */
bool scene_test_render(void)
{
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
		glTranslated(xpos, ypos, zpos + ((graph->prj[4] + graph->prj[5]) / 2));
		glRotated(view_x, 0.0, 1.0, 0.0);
		glRotated(view_y, 1.0, 0.0, 0.0);
		/* draw door */
		glPushMatrix();
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, -2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 2.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(-2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
		glPopMatrix();
		/* draw floor */
		glPushMatrix();
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
		glPopMatrix();
		/* draw walls */
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
		glPopMatrix();
		glPushMatrix();
			glRotated(90.0, 0.0, 0.0, -1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
		glPopMatrix();
		/* draw ceiling */
		glPushMatrix();
			glRotated(180.0, 0.0, 0.0, 1.0);
			glTranslated(-2.0, -4.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, -2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(2.0, 0.0, 0.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
			glTranslated(0.0, 0.0, 2.0);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, graph->root_node->vao_indicies);
		glPopMatrix();
	glPopMatrix();
	
	/* flush */
	glFlush();

	/* display */
	#ifdef WIN32
		SwapBuffers(dc);
	#else
		glXSwapBuffers(dpy, window);
	#endif /* WIN32 */
	
	return true;
}

/*
 * scene_test_input - handle movement
 */
bool scene_test_input(void)
{	
	/* movement */
	/* w - up */	if (key & KEY_W || key_held & KEY_W) zpos += 0.5;
	/* s - down */	if (key & KEY_S || key_held & KEY_S) zpos -= 0.5;
	/* a - left */	if (key & KEY_A || key_held & KEY_A) xpos += 0.1;
	/* d - right */ if (key & KEY_D || key_held & KEY_D) xpos -= 0.1;
	
	/* mouse controls view angle */
	if (mouse_moved_x) {
		view_x += 1.0 * (mouse_x_positive ? 1.0 : -1.0);
	}
	if (mouse_moved_y) {
		view_y += 1.0 * (mouse_y_positive ? 1.0 : -1.0);
	}
	
	/* actions */
	/* q - quit */	if (key & KEY_Q) quit = true;
	
	#ifndef NDEBUG
	/* v - uncapture mouse */	if (key & KEY_V) { mouse_captured = false; debug_cursor_changed = true; }
	/* c - uncapture mouse */	if (key & KEY_C) { mouse_captured = true;  debug_cursor_changed = true; }
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
	#endif /* NDEBUG */
	
	return true;
}

/*
 * scene_test_routine -  process object routine 
 */
bool scene_test_routine(void)
{
	view_x = fmod(view_x, 360);
	view_y = fmod(view_y, 360);
	//if (xpos > 3) xpos = 3;
	//if (xpos < -3) xpos = -3;
	if (ypos > 3) ypos = 3;
	if (ypos < -3) ypos = -3;
	//if (zpos > (-graph->prj[4] - 1) + 2) zpos = (-graph->prj[4] - 1) + 2;
	//if (zpos < -graph->prj[5] + 1) zpos = -graph->prj[5] + 1;
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
	
	free(graph->prj);
	free(graph);
	
	return true;
}

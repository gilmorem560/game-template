/*
 * stage - a single 3D playfield
 */
#include "stage.h"

static FILE *rgba_menu;
static FILE *rgba_font;
static texture_rgba *menu_texture;
static texture_rgba *font;

static GLdouble box_width_hot;
static GLdouble box_height_hot;
static const GLdouble box_width = 2.0;
static const GLdouble box_height = 2.0 / 3.0;
static const GLdouble box_pos_x = -1.0;
static const GLdouble box_pos_y = -1.0;
static bool box_display;

static GLdouble letter_height;
static GLdouble letter_width;
static bool print_message;
static GLdouble message_counter;
static const GLdouble message_pos = -0.9;
static const GLdouble message_length = 3.0;

/*
 * stage_init - OpenGL init
 */
bool stage_init(void)
{
	#ifndef NDEBUG
	printf("stage: init\n");
	#endif /* NDEBUG */
	
	/* enable GL states */
	glDisable(GL_DEPTH_TEST);	/* operating in 3D space */
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);		/* enable texturing */
	
	/* set background color */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	/* black background */
	
	/* back surface culling */
	glCullFace(GL_BACK);
	
	/* texture setup */
	rgba_menu = fopen("assets/rgba_menu.bin", "rb");
	menu_texture = texture_rgba_new(rgba_menu, 640, 160, 4);
	fclose(rgba_menu);
	
	rgba_font = fopen("assets/rgba_font.bin", "rb");
	font = texture_rgba_new(rgba_font, 97, 47, 4);
	fclose(rgba_font);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glGenTextures(1, &stage_menu_texture);
	glBindTexture(GL_TEXTURE_2D, stage_menu_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, menu_texture->width, menu_texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, menu_texture->data);
		
	glGenTextures(1, &stage_font_texture);
	glBindTexture(GL_TEXTURE_2D, stage_font_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, font->width, font->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, font->data);

	/* setup projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	box_width_hot = 0.0;
	box_height_hot = 0.0;
	box_display = false;
	letter_height = font->height;
	letter_width = font->width / 3.0;
	print_message = false;
	message_counter = 0.0;
	
	return true;
}

/*
 * stage_render - OpenGL rendering
 */
bool stage_render(void)
{
	/* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
	
	/* begin rendering models */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	
		/* render box */
		glBindTexture(GL_TEXTURE_2D, stage_menu_texture);
		glBegin(GL_QUADS);
			glColor3d(0.0, 0.0, 0.0);
			glTexCoord2d(0.0, 0.0);
			glVertex3d(box_pos_x, box_pos_y, 0.0);
			glTexCoord2d(1.0, 0.0);
			glVertex3d(box_pos_x + box_width_hot, box_pos_y, 0.0);
			glTexCoord2d(1.0, 1.0);
			glVertex3d(box_pos_x + box_width_hot, box_pos_y + box_height_hot, 0.0);
			glTexCoord2d(0.0, 1.0);
			glVertex3d(box_pos_x, box_pos_y + box_height_hot, 0.0);
		glEnd();
		
		/* render text */
		if (print_message && message_counter > 1.0) {
			glBindTexture(GL_TEXTURE_2D, stage_font_texture);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0);
				glVertex3d(message_pos, 1.0 - (0.1 + letter_height), 0.0);
				glTexCoord2d(letter_width, 0.0);
				glVertex3d(message_pos + letter_width, 1.0 - (0.1 + letter_height), 0.0);
				glTexCoord2d(letter_width, letter_height);
				glVertex3d(message_pos + letter_width, 0.9, 0.0);
				glTexCoord2d(0.0, letter_height);
				glVertex3d(message_pos, 0.9, 0.0);
				if (message_counter > 2.0) {
					glTexCoord2d(letter_width, 0.0);
					glVertex3d(message_pos + letter_width, 1.0 - (0.1 + letter_height), 0.0);
					glTexCoord2d(letter_width * 2, 0.0);
					glVertex3d(message_pos + (letter_width * 2), 1.0 - (0.1 + letter_height), 0.0);
					glTexCoord2d(letter_width * 2, letter_height);
					glVertex3d(message_pos + (letter_width * 2), 0.9, 0.0);
					glTexCoord2d(letter_width, letter_height);
					glVertex3d(message_pos + letter_width, 0.9, 0.0);
					if (message_counter > 3.0) {
						glTexCoord2d(letter_width * 2, 0.0);
						glVertex3d(message_pos + (letter_width * 2), 1.0 - (0.1 + letter_height), 0.0);
						glTexCoord2d(letter_width * 3, 0.0);
						glVertex3d(message_pos + (letter_width * 3), 1.0 - (0.1 + letter_height), 0.0);
						glTexCoord2d(letter_width * 3, letter_height);
						glVertex3d(message_pos + (letter_width * 3), 0.9, 0.0);
						glTexCoord2d(letter_width * 2, letter_height);
						glVertex3d(message_pos + (letter_width * 2), 0.9, 0.0);
					}
				}
			glEnd();
		}
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
 * stage_input - handle movement
 */
bool stage_input(void)
{	
	/* actions */
	/* d - display box */	if (key & KEY_D) box_display = true;
	/* w - wipe box */		if (key & KEY_W) box_display = false;
	/* q - quit */	if (key & KEY_Q) quit = true;
	
	#ifndef NDEBUG
	/* hot mode switching for debugging */
	if (KEY_ISNUM(key) && !(key & KEY_4)) {
		stage_free();
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
			default:
				quit = true;
				break;
		}
	}
	#endif /* NDEBUG */
	
	return true;
}

/*
 * stage_routine -  process object routine 
 */
bool stage_routine(void)
{
	/* movement */
		/* expand */
		if (box_display) {
			box_width_hot += 0.1;
			box_height_hot += 0.1;
		} else {
			box_width_hot -= 0.1;
			box_height_hot -= 0.1;
		}
	
	/* constraints */
		/* size */
		if (box_width_hot > box_width) box_width_hot = box_width;
		if (box_width_hot < 0.0) box_width_hot = 0.0;
		
		if (box_height_hot > box_height) box_height_hot = box_height;
		if (box_height_hot < 0.0) box_height_hot = 0.0;
		
	/* conditional action */
		if (box_width_hot == box_width && box_height_hot == box_height) {
			/* begin printing text */
			print_message = true;
			message_counter += 0.01;
			if (message_counter > 3.0)
				message_counter = 3.0;
		}
		
	return true;
}

/*
 * stage_free - OpenGL free
 */
bool stage_free(void)
{
	#ifndef NDEBUG
	printf("stage: free\n");
	#endif /* NDEBUG */
	
	glDeleteTextures(1, &stage_menu_texture);
	texture_free(menu_texture);
	glDeleteTextures(1, &stage_font_texture);
	texture_free(font);
	
	return true;
}

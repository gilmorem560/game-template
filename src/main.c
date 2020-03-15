/*
 * main - entry point
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _WIN32
#include "../config.h"
#endif  /* _WIN32 */

/* graphics handler */
#include "graphics/contexts/glcontext.h"

/* input handler */
#include "input/input.h"

/* basic objects */
#include "graphics/primitives/coord.h"
#include "graphics/primitives/prim.h"

/* composite objects */
#include "graphics/objects/hedrons.h"

bool renderframe(void); /* OpenGL rendering cycle */
bool move(void);        /* handle movement based on key masks */

/* octahedron */
GLint diamond1, diamond2, diamond3, diamond4, diamond5;

int angle = 0;

#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
    key = 0;    /* initialize key bitfield here for now */
    quit = false;

    /* initialize OpenGL for X11 */
    glxinit();
    
    /* create lists */
    diamond1 = glGenLists(1);
    glNewList(diamond1, GL_COMPILE);
    octahedron(0.5, 0.5, 0.5);
    glEndList();
    
    diamond2 = glGenLists(1);
    glNewList(diamond2, GL_COMPILE);
    octahedron(0.5, 0.5, 0.5);
    glEndList();
    
    diamond3 = glGenLists(1);
    glNewList(diamond3, GL_COMPILE);
    octahedron(0.5, 0.5, 0.5);
    glEndList();
    
    diamond4 = glGenLists(1);
    glNewList(diamond4, GL_COMPILE);
    octahedron(0.5, 0.5, 0.5);
    glEndList();
    
    diamond5 = glGenLists(1);
    glNewList(diamond5, GL_COMPILE);
    octahedron(0.5, 0.5, 0.5);
    glEndList();
        
    /* main loop */
    while (!quit) {
        /* render next frame */
        if (!renderframe()) {
            fprintf(stderr, "renderframe: failure\n");
        } else {
            glXSwapBuffers(dpy, window);
        }

        /* begin processing events */
        if (XPending(dpy))
            glxevent(dpy);
        
        /* process movement */
        move();
        
        /* prepare for next frame */
	if (angle == 360)
            angle = 0;
    }
    
    /* destroy lists */
    glDeleteLists(diamond1, 1);
    glDeleteLists(diamond2, 1);
    glDeleteLists(diamond3, 1);
    glDeleteLists(diamond4, 1);
    glDeleteLists(diamond5, 1);
    
    /* close OpenGL for X11 */
    glxfree();
    
    return EXIT_SUCCESS;
}
#else   /* _WIN32 */
/*
 * WinMain - windows entry point
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    key = 0;    /* initialize key bitfield here for now */
    quit = false;
    angle = 1;
    
    /* initialize OpenGL for WinAPI */
    wglinit(hInstance, nShowCmd, wndproc);

    /* main loop */
    while (!quit) {
        /* render next frame */
        if (!renderframe()) {
            fprintf(stderr, "renderframe: failure\n");
        } else {
            SwapBuffers(dc);
        }

        /* begin processing events */
        wglevent(wnd);
        
        /* process movement */
        move();
        
        /* prepare for next frame */
    }

    /* close OpenGL for WinAPI */
    wglfree(hInstance);

    return EXIT_SUCCESS;
}
#endif  /* _WIN32 */

/*
 * renderframe - OpenGL rendering cycle
 */
bool renderframe(void)
{
    /* clear the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glPushMatrix();
	glTranslated(0.5, 0.5, 0.0);
	glRotated(angle, 0.0, 1.0, 0.0);
	glCallList(diamond1);
    glPopMatrix();
    
    glPushMatrix();
	glTranslated(0.5, -0.5, 0.0);
	glRotated(angle, 0.0, 1.0, 0.0);
	glCallList(diamond2);
    glPopMatrix();
    
    glPushMatrix();
	glTranslated(-0.5, 0.5, 0.0);
	glRotated(angle, 0.0, -1.0, 0.0);
	glCallList(diamond3);
    glPopMatrix();
    
    glPushMatrix();
	glTranslated(-0.5, -0.5, 0.0);
	glRotated(angle, 0.0, -1.0, 0.0);
	glCallList(diamond4);
    glPopMatrix();
    
    glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glRotated(angle, 1.0, 0.0, 0.0);
	glCallList(diamond4);
    glPopMatrix();
        
    return true;
}

/*
 * move - handle movement based on key masks 
 */
bool move(void)
{
    int a = 0;
    
    /* f - fullscreen */
    if (key & KEY_F) {
	/*    
        if (isfull) {
            setwindowed();
            isfull = false;
        } else {
            setfullscreen();
            isfull = true;
        }
        key &= ~KEY_F;
	*/
    }
    
    /* m - move model */
    if (key & KEY_M) {

    }
    
    /* q - quit */
    if (key & KEY_Q) {
        quit = true;
    }
    
    /* r - rotate model */
    if (key & KEY_R) {
	angle++;
    }
    
    return true;
}

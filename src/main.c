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

bool renderframe(void); /* OpenGL rendering cycle */
bool move(void);        /* handle movement based on key masks */

/* test objects */
point3d point1 = { 0.0 , 1.0, 0.0 };
point3d point2 = { 0.0, -1.0, 0.0 };
point3d point3 = { 0.5, 0.0, -0.5 };
point3d point4 = { 0.5, 0.0, 0.5 };
point3d point5 = { -0.5, 0.0, 0.5 };
point3d point6 = { -0.5, 0.0, -0.5 };
tri3d *triangle1;
tri3d *triangle2;
tri3d *triangle3;
tri3d *triangle4;
tri3d *triangle5;
tri3d *triangle6;
tri3d *triangle7;
tri3d *triangle8;
bool tri1l = false;
bool tri2l = false;
int angle;
bool isfull = false;

#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
    key = 0;    /* initialize key bitfield here for now */
    quit = false;
    angle = 1;
    
    /* test triangles */
    triangle1 = new_poly3d(3, point1, point3, point4);
    triangle2 = new_poly3d(3, point1, point4, point5);
    triangle3 = new_poly3d(3, point1, point5, point6);
    triangle4 = new_poly3d(3, point1, point6, point3);
    triangle5 = new_poly3d(3, point2, point3, point4);
    triangle6 = new_poly3d(3, point2, point4, point5);
    triangle7 = new_poly3d(3, point2, point5, point6);
    triangle8 = new_poly3d(3, point2, point6, point3);

    /* initialize OpenGL for X11 */
    glxinit();
        
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
    
    /* draw some triangles */
    draw_tri3d(triangle1, 1.0, 0.0, 0.0);
    draw_tri3d(triangle2, 0.0, 1.0, 0.0);
    draw_tri3d(triangle3, 0.0, 0.0, 1.0);
    draw_tri3d(triangle4, 1.0, 1.0, 0.0);
    draw_tri3d(triangle5, 0.0, 1.0, 1.0);
    draw_tri3d(triangle6, 1.0, 0.0, 1.0);
    draw_tri3d(triangle7, 1.0, 1.0, 1.0);
    draw_tri3d(triangle8, 0.0, 0.0, 0.0);
        
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
        if (isfull) {
            setwindowed();
            isfull = false;
        } else {
            setfullscreen();
            isfull = true;
        }
        key &= ~KEY_F;
    }
    
    /* m - move model */
    if (key & KEY_M) {
        if (triangle1->points[2].x > 1.0)
            tri1l = true;
        else if (triangle1->points[2].x < -1.0)
            tri1l = false;
                        
        if (triangle2->points[2].x > 1.0)
            tri2l = true;
        else if (triangle2->points[2].x < -1.0)
            tri2l = false;
                    
        for (a = 0; a < 3; a++) {
            if (tri1l)
                triangle1->points[a].x -= 0.1;
            else
                triangle1->points[a].x += 0.1;
                        
            if (tri2l)
                triangle2->points[a].x -= 0.1;
            else
                triangle2->points[a].x += 0.1;
        }
    }
    
    /* q - quit */
    if (key & KEY_Q) {
        quit = true;
    }
    
    /* r - rotate model */
    if (key & KEY_R) {
        glRotated(angle, 0, 1, 0);
    }
    
    return true;
}

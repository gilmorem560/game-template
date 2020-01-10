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
#ifndef _WIN32
#include "graphics/contexts/glxcontext.h"
#else   /* _WIN32 */
#include "graphics/contexts/wglcontext.h"
#endif  /* linux, _WIN32 */

/* input handler */
#include "input/input.h"

/* basic objects */
#include "graphics/primitives/coord.h"
#include "graphics/primitives/prim.h"

bool renderframe(void); /* OpenGL rendering cycle */
bool move(void);        /* handle movement based on key masks */

/* test objects */
point3d point1 = { 0.0, 1.0, 0.0 };
point3d point2 = { -1.0, 0.0, 0.0 };
point3d point3 = { 1.0, 0.0, 0.0 };
point3d point4 = { 0.0, -1.0, 0.0 };
tri3d *triangle1;
tri3d *triangle2;
bool tri1l = false;
bool tri2l = false;
bool quit = false;

#ifndef _WIN32
/*
 * main - entry point
 */
int main(int argc, char *argv[])
{
    key = 0;    /* initialize key bitfield here for now */
    
    /* test triangles */
    triangle1 = new_poly3d(3, point1, point2, point3);
    triangle2 = new_poly3d(3, point4, point2, point3);

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
        glxevent(dpy);
        
        /* process movement */
        move();
        
        /* prepare for next frame */
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
    draw_tri3d(triangle1, 0.0, 1.0, 0.0);
    draw_tri3d(triangle2, 0.0, 0.0, 1.0);
        
    return true;
}

/*
 * move - handle movement based on key masks 
 */
bool move(void)
{
    int a = 0;
    
    /* m - move model */
    if (key & KEY_M) {
        if (triangle1->points[0].x >= 1.0)
            tri1l = true;
        else if (triangle1->points[0].x <= -1.0)
            tri1l = false;
                        
        if (triangle2->points[0].x >= 1.0)
            tri2l = true;
        else if (triangle2->points[0].x <= -1.0)
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
        key &= ~KEY_M;
    }
    
    /* q - quit */
    if (key & KEY_Q) {
        quit = true;
    }
    
    return true;
}

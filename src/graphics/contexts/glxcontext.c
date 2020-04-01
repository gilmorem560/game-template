 /*
  * glxcontext - OpenGL for X11
  */
#include <stdlib.h>
#include <stdio.h>

#include "glcontext.h"

/*
 * glxinit - initialize OpenGL for X11
 */
void glxinit(int xres, int yres)
{
    XSetWindowAttributes attrs;
    int major, minor;
    int config_count;
    dpy = NULL;
    vis = NULL;
    
    /* open X display */
    dpy = XOpenDisplay(NULL);
        if (dpy == NULL) {
            fprintf(stderr, "glxinit: could not open X11 display\n");
            exit(EXIT_FAILURE);
        }
    
    /* query GLX version */
    if (!glXQueryVersion(dpy, &major, &minor)) {
        fprintf(stderr, "glxinit: could not query version\n");
        XCloseDisplay(dpy);
        exit(EXIT_FAILURE);
    }
    
    /* check that it is sufficient */
    if (decimal(major, minor) < 1.3) {
        fprintf(stderr, "glxinit: version 1.3 or greater required, version %f detected\n", decimal(major, minor));
        XCloseDisplay(dpy);
        exit(EXIT_FAILURE);
    }
    
    /* determine default screen */
    screen_number = XDefaultScreen(dpy);
    
    /* retrieve root window */
    root = XRootWindow(dpy, screen_number);
    
    /* set framebuffer attributes */
    int attrib_list[] = {
        GLX_X_RENDERABLE    ,True
        ,GLX_DRAWABLE_TYPE  ,GLX_WINDOW_BIT
        ,GLX_RENDER_TYPE    ,GLX_RGBA_BIT
        ,GLX_X_VISUAL_TYPE  ,GLX_TRUE_COLOR
        ,GLX_RED_SIZE       ,8
        ,GLX_GREEN_SIZE     ,8
        ,GLX_BLUE_SIZE      ,8
        ,GLX_ALPHA_SIZE     ,8
        ,GLX_DEPTH_SIZE     ,24
        ,GLX_STENCIL_SIZE   ,8
        ,GLX_DOUBLEBUFFER   ,True
        ,None
    };
    
    /* get framebuffer config */
    config = glXChooseFBConfig(dpy, screen_number, attrib_list, &config_count);
        if (config == NULL) {
            fprintf(stderr, "glxinit: could not retrieve fb config\n");
            XCloseDisplay(dpy);
            exit(EXIT_FAILURE);
        }
    
    /* retrieve X visual info */
    vis = glXGetVisualFromFBConfig(dpy, *config);
        if (vis == NULL) {
            fprintf(stderr, "glxinit: could not retrieve visual\n");
            XFree(config);
            XCloseDisplay(dpy);
            exit(EXIT_FAILURE);
        }
    
    /* create context */
    context = glXCreateContext(dpy, vis, NULL, True);
        if (context == NULL) {
            fprintf(stderr, "glxinit: could not retrieve context\n");
            XFree(vis);
            XFree(config);
            XCloseDisplay(dpy);
            exit(EXIT_FAILURE);
        }
    
    /* set input events */
    attrs.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask;
    
    /* create window */
    win = XCreateWindow(
        dpy                 /* Display *display */
        ,root               /* Window parent */
        ,400                /* int x */
        ,400                /* int y */
        ,xres               /* unsigned int width */
        ,yres               /* unsigned int height */
        ,1                  /* unsigned int border_width */
        ,CopyFromParent     /* int depth */
        ,CopyFromParent     /* unsigned int class */
        ,vis->visual        /* Visual *visual */
        ,CWEventMask        /* unsigned long valuemask */
        ,&attrs);             /* XSetWindowAttributes *attributes */
    
    /* allow auto-repeat of keys */
    XkbSetDetectableAutoRepeat(dpy, True, NULL);
    
    /* create on-screen rendering area */
    window = glXCreateWindow(dpy, *config, win, NULL);
    
    /* associate context to window */
    if (!glXMakeCurrent(dpy, window, context)) {
        fprintf(stderr, "glxinit: could not associate context with window\n");
        glXDestroyWindow(dpy, window);
        XDestroyWindow(dpy, win);
        glXDestroyContext(dpy, context);
        XFree(vis);
        XFree(config);
        XCloseDisplay(dpy);
        exit(EXIT_FAILURE);
    }
    
    /* set name */
    XStoreName(dpy, win, "OpenGL");
    
    /* display window */
    XMapWindow(dpy, win);
    
    return;
}

/*
 * glxfree - close OpenGL for X11
 */
void glxfree(void)
{
    /* hide window */
    XUnmapWindow(dpy, win);
    
    /* dissociate context from window */
    glXMakeCurrent(dpy, None, NULL);
    
    /* destroy on-screen rendering area */
    glXDestroyWindow(dpy, window);
    
    /* destroy window */
    XDestroyWindow(dpy, win);
    
    /* destroy context */
    glXDestroyContext(dpy, context);
    
    /* free X visual info */
    XFree(vis);
    
    /* free framebuffer config */
    XFree(config);
    
    /* close X display */
    XCloseDisplay(dpy);
    
    return;
}
 /*
  * glxcontext - OpenGL for X11
  */
#include "glcontext.h"

/*
 * glxinit - initialize OpenGL for X11
 */
void glxinit()
{
    XSetWindowAttributes attrs;
	XColor cursor_color = { 0, 0, 0, 0, 0, 0 };
	Pixmap cursor_pixmap;
	const char null_bitmap[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
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
    
    /* determine default screen */
    screen_number = XDefaultScreen(dpy);
	
	/* get resolution */
	xres = XDisplayWidth(dpy, screen_number);
	yres = XDisplayHeight(dpy, screen_number);
    
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
    attrs.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | PointerMotionMask;
	attrs.override_redirect = True;
    
    /* create window */
    win = XCreateWindow(
        dpy                 /* Display *display */
        ,root               /* Window parent */
        ,0                  /* int x */
        ,0	                /* int y */
        ,xres               /* unsigned int width */
        ,yres               /* unsigned int height */
        ,1                  /* unsigned int border_width */
        ,CopyFromParent     /* int depth */
        ,CopyFromParent     /* unsigned int class */
        ,vis->visual        /* Visual *visual */
        ,CWEventMask | CWOverrideRedirect /* unsigned long valuemask */
        ,&attrs);             /* XSetWindowAttributes *attributes */
    
    /* allow auto-repeat of keys */
    XkbSetDetectableAutoRepeat(dpy, True, NULL);
    
    /* create on-screen rendering area */
    window = glXCreateWindow(dpy, *config, win, NULL);
	
	/* create invisible cursor pixmap */
	cursor_pixmap = XCreateBitmapFromData(dpy, win, null_bitmap, 8, 8);
	
	/* create custom (invisible) cursor - modes must implement cursors */
	cursor = XCreatePixmapCursor(dpy, cursor_pixmap, cursor_pixmap, &cursor_color, &cursor_color, 0, 0);
	
	/* free pixmap now that we're done */
	XFreePixmap(dpy, cursor_pixmap);
	
	/* associate it */
	XDefineCursor(dpy, win, cursor);
    
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
	
	/* grab keyboard */
	XGrabKeyboard(dpy, win, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    
    return;
}

/*
 * glxfree - close OpenGL for X11
 */
void glxfree(void)
{
	XSetWindowAttributes attrs;
		attrs.override_redirect = False;
		
	/* ungrab keyboard */
	XUngrabKeyboard(dpy, CurrentTime);
	
    /* hide window */
    XUnmapWindow(dpy, win);
    
    /* dissociate context from window */
    glXMakeCurrent(dpy, None, NULL);
	
	/* return visible cursor */
	XUndefineCursor(dpy, win);
    
    /* destroy on-screen rendering area */
    glXDestroyWindow(dpy, window);
	
	/* need to return the window to the window manager to close properly */
	XChangeWindowAttributes(dpy, win, CWOverrideRedirect, &attrs);
    
    /* destroy window */
    XDestroyWindow(dpy, win);
	
	/* delete cursor */
	XFreeCursor(dpy, cursor);
    
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

void setwindowed(unsigned short w_xres, unsigned short w_yres)
{
	if (isfullscreen) {
		XSetWindowAttributes attrs;
		attrs.override_redirect = False;
		
		/* ungrab keyboard */
		XUngrabKeyboard(dpy, CurrentTime);
		
		/* hide window */
		XUnmapWindow(dpy, win);
		
		/* dissociate context from window */
		glXMakeCurrent(dpy, None, NULL);
		
		/* destroy on-screen rendering area */
		glXDestroyWindow(dpy, window);
		
		/* return control to window manager */
		XChangeWindowAttributes(dpy, win, CWOverrideRedirect, &attrs);
		
		/* resize window */
		XResizeWindow(dpy, win, w_xres, w_yres);
		
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
		
		/* reshow window */
		XMapWindow(dpy, win);
		
		XGrabKeyboard(dpy, win, False, GrabModeAsync, GrabModeAsync, CurrentTime);
		
		/* mark windowed */
		isfullscreen = false;
	}
	
	return;
}

void setfullscreen(void)
{
	if (!isfullscreen) {
		XSetWindowAttributes attrs;
		attrs.override_redirect = True;
		
		/* hide window */
		XUnmapWindow(dpy, win);
		
		/* dissociate context from window */
		glXMakeCurrent(dpy, None, NULL);
		
		/* destroy on-screen rendering area */
		glXDestroyWindow(dpy, window);
		
		/* take control from window manager */
		XChangeWindowAttributes(dpy, win, CWOverrideRedirect, &attrs);
		
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
		
		/* resize window */
		XMoveResizeWindow(dpy, win, 0, 0, xres, yres);
		
		/* unhide window */
		XMapWindow(dpy, win);
		
		/* grab keyboard */
		XGrabKeyboard(dpy, win, False, GrabModeAsync, GrabModeAsync, CurrentTime);
	
		/* mark fullscreen */
		isfullscreen = true;
	}
	
	return;
}

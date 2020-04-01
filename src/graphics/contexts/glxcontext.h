/*
 * glxcontext - OpenGL for X11
 */
#ifndef __GLXCONTEXT_H__
#define __GLXCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
#include "../../../config.h"

#include <X11/Xlib.h>   /* X11 libraries */
#include <X11/XKBlib.h>	/* X11 Xkb extensions */
#ifdef  HAVE_GL_GL_H    /* OpenGL libraries */
#include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#include <OpenGL/gl.h>
#endif /* HAVE_GL_GL_H, HAVE_OPENGL_GL_H */
#ifdef  HAVE_GL_GLX_H   /* OpenGL X11 extensions */
#include <GL/glx.h>
#elif defined(HAVE_OPENGL_GLX_H)
#include <OpenGL/glx.h>
#endif /* HAVE_GL_GLX_H, HAVE_OPENGL_GLX_H */
    
#include "../../util/macros.h"     /* useful macros */
    
/* X11 variables */
Display *dpy;
XVisualInfo *vis;
Window win;
Window root;
    unsigned long rootSizeX;
    unsigned long rootSizeY;
int screen_number;

/* GLX variables */
GLXFBConfig *config;
GLXContext context;
GLXWindow window;

/* glxinit - initialize OpenGL for X11 */
void glxinit(int xres, int yres);

/* glxfree - close OpenGL for X11 */
void glxfree(void);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __GLXCONTEXT_H__ */

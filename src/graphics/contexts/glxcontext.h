/*
 * glxcontext - OpenGL for X11
 */
#ifndef __GLXCONTEXT_H__
#define __GLXCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
#include "../../../config.h"

#include <X11/Xlib.h>   	/* X11 libraries */
#include <X11/XKBlib.h>		/* X11 Xkb extensions */
#include <X11/cursorfont.h>	/* X11 cursor fonts */
#ifdef  HAVE_GL_GL_H    	/* OpenGL libraries */
#include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#include <OpenGL/gl.h>
#endif /* HAVE_GL_GL_H, HAVE_OPENGL_GL_H */
#ifdef  HAVE_GL_GLX_H   	/* OpenGL X11 extensions */
#include <GL/glx.h>
#elif defined(HAVE_OPENGL_GLX_H)
#include <OpenGL/glx.h>
#endif /* HAVE_GL_GLX_H, HAVE_OPENGL_GLX_H */
    
#include "../../util/macros.h"     /* useful macros */
    
/* X11 variables */
extern Display *dpy;
extern XVisualInfo *vis;
extern Window win;
extern Cursor cursor;
extern Window root;
    extern unsigned long rootSizeX;
    extern unsigned long rootSizeY;
extern int screen_number;

/* GLX variables */
extern GLXFBConfig *config;
extern GLXContext context;
extern GLXWindow window;

/* glxinit - initialize OpenGL for X11 */
extern void glxinit();

/* glxfree - close OpenGL for X11 */
extern void glxfree(void);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __GLXCONTEXT_H__ */

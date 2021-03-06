/* glcontext - meta-header for OpenGL graphics */
#ifndef __GLCONTEXT_H__
#define __GLCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* library includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#include "wglcontext.h"
#else
#include "glxcontext.h"
#endif /* _WIN32 */

#define DEFAULT_WIDTH    640
#define DEFAULT_HEIGHT   480
unsigned short xres;
unsigned short yres;
double current_ratio;
bool isfullscreen;

void drawframe();
void setwindowed(unsigned short w_xres, unsigned short w_yres);
void setfullscreen(void);

#ifndef NDEBUG
static GLenum gl_errno;
#endif /* NDEBUG */
    
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __GLCONTEXT_H__ */



/*
 * macros - useful macros
 */
#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif /* _WIN32 */

#include <math.h>

/* if there were macros you would see them here */
#define	degtorad(x)	(x / 360.0) * 2.0 * M_PI
#define radtodeg(x) (x * 360) / (2.0 * M_PI)

/* debugging functionality */

#ifndef NDEBUG

/*
 * drop in debug inspector, pulls errors sitting on the stack at insertion point
 * using standard C streams, pipeable
 */
#define INSPECT_GL 		while ((gl_errno = glGetError()) != GL_NO_ERROR) { \
							if (gl_errno | GL_INVALID_ENUM) \
								fputs("OpenGL: Invalid enum\n", stderr); \
							else if (gl_errno | GL_INVALID_VALUE) \
								fputs("OpenGL: Invalid value\n", stderr); \
							else if (gl_errno | GL_INVALID_OPERATION) \
								fputs("OpenGL: Invalid operation\n", stderr); \
							else if (gl_errno | GL_OUT_OF_MEMORY) \
								fputs("OpenGL: Out of memory\n", stderr); \
							else \
								fprintf(stderr, "OpenGL: Undefined error %d\n", gl_errno); \
						} \
						printf("OpenGL: Error inspection complete.\n"); \
												

/* drop in gdb interrupt */
#define GDB_INTERRUPT raise(SIGINT);

/* debugging key handlers, hold t + key */
#define debug_pollkeys(key) \
						if (key & KEY_T) { \
/* q - quit */				if (key & KEY_Q) quit = true;	/* must be after modeswitch or free will happen twice */ \
/* r - windowed */			if (key & KEY_R) { setwindowed(640, 480); key &= ~KEY_R; } \
/* f - fullscreen */		if (key & KEY_F) { setfullscreen(); key &= ~KEY_F; } \
/* v - uncapture mouse */	if (key & KEY_V) { mouse_captured = false; debug_cursor_changed = true; } \
/* c - uncapture mouse */	if (key & KEY_C) { mouse_captured = true;  debug_cursor_changed = true; } \
/* b - break (gdb) */		if (key & KEY_B) GDB_INTERRUPT \
						}

#endif /* NDEBUG */

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MACROS_H__ */

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

/* drop in debug inspector, pulls errors sitting on the stack at insertion point 
 * GLenum gl_errno - a GLenum to hold the state
 */
#define debug_inspectglerrors(gl_errno) 		while ((gl_errno = glGetError()) != GL_NO_ERROR) { \
													if (gl_errno | GL_INVALID_ENUM) \
														fprintf(stderr, "OpenGL: Invalid enum\n"); \
													else if (gl_errno | GL_INVALID_VALUE) \
														fprintf(stderr, "OpenGL: Invalid value\n"); \
													else if (gl_errno | GL_INVALID_OPERATION) \
														fprintf(stderr, "OpenGL: Invalid operation\n"); \
													else if (gl_errno | GL_OUT_OF_MEMORY) \
														fprintf(stderr, "OpenGL: Out of memory\n"); \
													else \
														fprintf(stderr, "OpenGL: Undefined error %d\n", gl_errno); \
												} \
												fprintf(stderr, "OpenGL: Error inspection complete.\n"); \

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MACROS_H__ */

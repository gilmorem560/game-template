/* glcontext - meta-header for OpenGL graphics */
#ifndef __GLCONTEXT_H__
#define __GLCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _WIN32
#include "wglcontext.h"
#else
#include "glxcontext.h"
#endif /* _WIN32 */
    
void setwindowed(void);
void setfullscreen(void);
    
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __GLCONTEXT_H__ */

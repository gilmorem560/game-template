/*
 * wglcontext - OpenGL for WinAPI
 */
#ifndef __WGLCONTEXT_H__
#define __WGLCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <Windows.h>    /* WinAPI libraries */
#include <GL/gl.h>      /* OpenGL libraries */
    
#include "../../util/macros.h"     /* useful macros */

/* WinAPI variables */
WNDCLASS wndclass;
HMONITOR monitor;
HWND wnd;
HDC dc;

/* WGL variables */
HGLRC context;

/* wglinit - initialize OpenGL for WinAPI */
void wglinit(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

/* wglfree - close OpenGL for WinAPI */
void wglfree(HINSTANCE hInstance);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __WGLCONTEXT_H__ */

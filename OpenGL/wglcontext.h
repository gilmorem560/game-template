#ifndef __WGLCONTEXT_H__
#define __WGLCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <Windows.h>

#include <GL/gl.h>

WNDCLASS wndclass;
HWND wnd;
HDC dc;

HGLRC context;

void wglinit(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);
void wglexit(HINSTANCE hInstance);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __WGLCONTEXT_H__ */
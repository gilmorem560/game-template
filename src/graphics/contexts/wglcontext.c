/*
 * wglcontext - OpenGL for WinAPI
 */
#include <stdio.h>
#include <stdlib.h>

#include "wglcontext.h"

/*
 * wglinit - initialize OpenGL for WinAPI
 */
void wglinit(HINSTANCE hInstance, int nShowCmd, WNDPROC wndproc)
{
	int pixel_format = 0;
    
    /* query WGL version */

	/* register window class */
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.lpfnWndProc = wndproc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = L"MainMenu";
	wndclass.lpszClassName = L"MainWndClass";
	RegisterClass(&wndclass);

	/* set pixel format attributes */
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR)
		,1
		,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER
		,PFD_TYPE_RGBA
		,32
		,0, 0, 0, 0, 0, 0
		,0
		,0
		,0
		,0, 0, 0, 0
		,24
		,8
		,0
		,PFD_MAIN_PLANE
		,0
		,0, 0, 0
	};

	/* create window */
	wnd = CreateWindow(
		L"MainWndClass"
		,L"OpenGL"
		,WS_OVERLAPPEDWINDOW
		,CW_USEDEFAULT
		,CW_USEDEFAULT
		,640
		,480
		,(HWND) NULL
		,(HMENU) NULL
		,hInstance
		,(LPVOID) NULL
	);
		if (!wnd) {
			fprintf(stderr, "wglinit: could not create window\n");
			UnregisterClass(L"MainWndClass", hInstance);
			exit(EXIT_FAILURE);
		}

	/* retrieve device context */
	dc = GetDC(wnd);
		if (dc == NULL) {
			fprintf(stderr, "wglinit: could not retrieve device context\n");
			DestroyWindow(wnd);
			UnregisterClass(L"MainWndClass", hInstance);
			exit(EXIT_FAILURE);
		}

	/* set pixel format */
	pixel_format = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixel_format, &pfd);

	/* create context */
	context = wglCreateContext(dc);

	/* associate context to window */
	wglMakeCurrent(dc, context);

	/* display window */
	ShowWindow(wnd, nShowCmd);
		if (!UpdateWindow(wnd)) {
			fprintf(stderr, "wglinit: could not update window\n");
			DestroyWindow(wnd);
			UnregisterClass(L"MainWndClass", hInstance);
			exit(EXIT_FAILURE);
		}

	return;
}

/*
 * wglfree - close OpenGL for X11
 */
void wglfree(HINSTANCE hInstance)
{
	/* hide window */
	ShowWindow(wnd, SW_HIDE);

	/* dissociate context from window */
	wglMakeCurrent(NULL, NULL);

	/* destroy context */
	wglDeleteContext(context);

	/* release device context */
	ReleaseDC(wnd, dc);

	/* destroy window */
	DestroyWindow(wnd);

	/* unregister class */
	UnregisterClass(L"MainWndClass", hInstance);

	return;
}

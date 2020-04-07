/*
 * wglcontext - OpenGL for WinAPI
 */
#include "glcontext.h"

#ifndef NDEBUG
HANDLE hStdin;
HANDLE hStdout;
DWORD stdinOldMode;
DWORD stdoutOldMode;
#endif /* NDEBUG */

/*
 * wglinit - initialize OpenGL for WinAPI
 */
void wglinit(HINSTANCE hInstance, int nShowCmd, WNDPROC wndproc)
{
	int pixel_format = 0;
	POINT monitor_point = { 0, 0 };
	MONITORINFO monitor_info;
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	monitor_info.cbSize = sizeof (MONITORINFO);
	isfullscreen = true;

	/* save these properties for screen switching */
	wgl_hInstance = hInstance;
	wgl_nShowCmd = nShowCmd;

	#ifndef NDEBUG
	/* show a new console window for debugging if not launched from CLI already */
	if (AllocConsole()) {
		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleMode(hStdin, &stdinOldMode);
		GetConsoleMode(hStdout, &stdoutOldMode);

		SetConsoleMode(hStdin, 0);
		SetConsoleMode(hStdout, 0);

		printf("test\n");
	}
	#endif /* NDEBUG*/

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

	/* determine default monitor */
	monitor = MonitorFromPoint(monitor_point, MONITOR_DEFAULTTOPRIMARY);

	/* get monitor information */
	GetMonitorInfo(monitor, &monitor_info);

	/* get resolution */
	xres = (unsigned short) (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left);
	yres = (unsigned short) (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top);

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
		,WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
		,0
		,0
		,xres
		,yres
		,(HWND) NULL
		,(HMENU) NULL
		,hInstance
		,(LPVOID) NULL
	);
		if (!wnd) {
			fprintf(stderr, "wglinit: could not create window\n");
			UnregisterClass(L"MainWndClass", hInstance);
			#ifndef NDEBUG
			SetConsoleMode(hStdin, stdinOldMode);
			SetConsoleMode(hStdout, stdoutOldMode);
			FreeConsole();
			#endif /* NDEBUG */
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

	/* hide cursor */
	ShowCursor(FALSE);

	/* associate context to window */
	wglMakeCurrent(dc, context);

	/* pull in swap interval extension method */
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		if (wglSwapIntervalEXT == NULL) {
			fprintf(stderr, "wglinit: this system does not support wglSwapIntervalEXT\n");
			wglMakeCurrent(NULL, NULL);
			ShowCursor(TRUE);
			wglDeleteContext(context);
			ReleaseDC(wnd, dc);
			DestroyWindow(wnd);
			UnregisterClass(L"MainWndClass", hInstance);
			#ifndef NDEBUG
			SetConsoleMode(hStdin, stdinOldMode);
			SetConsoleMode(hStdout, stdoutOldMode);
			FreeConsole();
			#endif /* NDEBUG */
			exit(EXIT_FAILURE);
		}

	/* enable vsync */
	wglSwapIntervalEXT(1);

	/* display window */
	ShowWindow(wnd, nShowCmd);
		if (!UpdateWindow(wnd)) {
			fprintf(stderr, "wglinit: could not update window\n");
			wglMakeCurrent(NULL, NULL);
			ShowCursor(TRUE);
			wglDeleteContext(context);
			ReleaseDC(wnd, dc);
			DestroyWindow(wnd);
			UnregisterClass(L"MainWndClass", hInstance);
			#ifndef NDEBUG
			SetConsoleMode(hStdin, stdinOldMode);
			SetConsoleMode(hStdout, stdoutOldMode);
			FreeConsole();
			#endif /* NDEBUG */
			exit(EXIT_FAILURE);
		}

	/* force into foreground */
	SetForegroundWindow(wnd);

	/* assign input to window */
	SetFocus(wnd);

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

	/* show cursor */
	ShowCursor(TRUE);

	/* destroy context */
	wglDeleteContext(context);

	/* release device context */
	ReleaseDC(wnd, dc);

	/* destroy window */
	DestroyWindow(wnd);

	/* unregister class */
	UnregisterClass(L"MainWndClass", hInstance);

	#ifndef NDEBUG
	SetConsoleMode(hStdin, stdinOldMode);
	SetConsoleMode(hStdout, stdoutOldMode);
	FreeConsole();
	#endif /* NDEBUG */

	return;
}

void setwindowed(unsigned short w_xres, unsigned short w_yres)
{
	if (isfullscreen) {
		/* hide window */
		ShowWindow(wnd, SW_HIDE);

		/* dissociate context from window */
		wglMakeCurrent(NULL, NULL);

		/* show cursor */
		ShowCursor(TRUE);

		/* change window type */
		SetWindowLongPtr(wnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		/* resize window */
		SetWindowPos(wnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, w_xres, w_yres, SWP_NOMOVE);

		/* associate context to window */
		wglMakeCurrent(dc, context);

		/* resize GL viewport */
		glViewport(0, 0, w_xres, w_yres);

		/* display window */
		ShowWindow(wnd, wgl_nShowCmd);
		if (!UpdateWindow(wnd)) {
			fprintf(stderr, "wglinit: could not update window\n");
			DestroyWindow(wnd);
			UnregisterClass(L"MainWndClass", wgl_hInstance);
			exit(EXIT_FAILURE);
		}

		isfullscreen = false;
	}

	return;
}

void setfullscreen(void)
{
	if (!isfullscreen) {
		/* hide window */
		ShowWindow(wnd, SW_HIDE);

		/* dissociate context from window */
		wglMakeCurrent(NULL, NULL);

		/* hide cursor */
		ShowCursor(FALSE);

		/* change window type */
		SetWindowLongPtr(wnd, GWL_STYLE, WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		/* resize window */
		SetWindowPos(wnd, HWND_TOP, 0, 0, xres, yres, 0);

		/* associate context to window */
		wglMakeCurrent(dc, context);

		/* resize GL viewport */
		glViewport(0, 0, xres, yres);

		/* display window */
		ShowWindow(wnd, wgl_nShowCmd);
			if (!UpdateWindow(wnd)) {
				fprintf(stderr, "wglinit: could not update window\n");
				DestroyWindow(wnd);
				UnregisterClass(L"MainWndClass", wgl_hInstance);
				exit(EXIT_FAILURE);
			}

		/* force into foreground */
		SetForegroundWindow(wnd);

		/* assign input to window */
		SetFocus(wnd);

		isfullscreen = true;
	}

	return;
}
/*
 * main - entry point
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Graphics handler */
#include "wglcontext.h"

/* Basic objects */
#include "coord.h"
#include "prim.h"

/* wndproc - main windows message processing loop */
LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*
 * WinMain - windows entry point
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    /* loop messages */
    MSG msg;
    bool quit = false;

    /* initialize graphics */
    wglinit(hInstance, nShowCmd, wndproc);

    /* main loop */
    while (!quit) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glBegin(GL_TRIANGLES);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0.0, 1.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(-1.0, 0.0, 0.0);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.0, -1.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(-1.0, 0.0, 0.0);
        glEnd();

        SwapBuffers(dc);

        /* handle messages */
        switch (GetMessage(&msg, wnd, 0, 0)) {
        case -1:
            /* error */
            fprintf(stderr, "main: could not retrieve message\n");
            return EXIT_FAILURE;
        case 0:
            /* WM_QUIT */
            quit = true;
            break;
        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            break;
        }
    }

    /* close graphics */
    wglexit(hInstance);

    return EXIT_SUCCESS;
}

/*
 * wndproc - main windows message processing loop
 */
LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (wParam) {
        case 'Q':
        case 'q':
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
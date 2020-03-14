/*
 * wglevent - event processing for OpenGL in WinAPI
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "input.h"

/*
 * wglevent - event processing for OpenGL in WinAPI
 */
void wglevent(HWND hWnd)
{
    MSG msg;
    
    switch (GetMessage(&msg, hWnd, 0, 0)) {
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
        
    return;
}

/*
 * wndproc - Windows message handler
 */
LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
        #ifndef NDEBUG
        printf("WM_KEYDOWN\n");
        #endif /* NDEBUG */
        switch (wParam) {
        case 'Q':
        case 'q':
            key |= KEY_Q;
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

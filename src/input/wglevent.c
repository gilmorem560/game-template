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
    
    if(PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
        case 'R':
        case 'r':
            key |= KEY_R;
            break;
        default:
            break;
        }
        break;
    case WM_KEYUP:
        #ifndef NDEBUG
        printf("WM_KEYUP");
        #endif /* NDEBUG */
        switch (wParam) {
        case 'R':
        case 'r':
            key &= ~KEY_R;
            break;
        default:
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        quit = true;
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

/*
 * wglevent - event processing for OpenGL in WinAPI
 */
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
	    case 'A':
        case 'a':
            key |= KEY_A;
            break;
	    case 'D':
        case 'd':
            key |= KEY_D;
            break;
        case 'Q':
        case 'q':
            key |= KEY_Q;
            break;
        case 'R':
        case 'r':
            key |= KEY_R;
            break;
	    case 'S':
        case 's':
            key |= KEY_S;
            break;
	    case 'W':
        case 'w':
            key |= KEY_W;
            break;
	    case 'X':
        case 'x':
            key |= KEY_X;
            break;
	    case 'Z':
        case 'z':
            key |= KEY_Z;
            break;
		case '0':
			key |= KEY_0;
			break;
		case '1':
			key |= KEY_1;
			break;
		case '2':
			key |= KEY_2;
			break;
		case '3':
			key |= KEY_3;
			break;
		case '4':
			key |= KEY_4;
			break;
		case '5':
			key |= KEY_5;
			break;
		case '6':
			key |= KEY_6;
			break;
		case '7':
			key |= KEY_7;
			break;
		case '8':
			key |= KEY_8;
			break;
		case '9':
			key |= KEY_9;
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
	    case 'A':
        case 'a':
            key &= ~KEY_A;
            break;
	    case 'D':
        case 'd':
            key &= ~KEY_D;
            break;
        case 'R':
        case 'r':
            key &= ~KEY_R;
            break;
	    case 'S':
        case 's':
            key &= ~KEY_S;
            break;
	    case 'W':
        case 'w':
            key &= ~KEY_W;
            break;
	    case 'X':
        case 'x':
            key &= ~KEY_X;
            break;
	    case 'Z':
        case 'z':
            key &= ~KEY_Z;
            break;
		case '0':
			key &= ~KEY_0;
			break;
		case '1':
			key &= ~KEY_1;
			break;
		case '2':
			key &= ~KEY_2;
			break;
		case '3':
			key &= ~KEY_3;
			break;
		case '4':
			key &= ~KEY_4;
			break;
		case '5':
			key &= ~KEY_5;
			break;
		case '6':
			key &= ~KEY_6;
			break;
		case '7':
			key &= ~KEY_7;
			break;
		case '8':
			key &= ~KEY_8;
			break;
		case '9':
			key &= ~KEY_9;
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

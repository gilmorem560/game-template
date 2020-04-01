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
			if (key & KEY_A)
				key_held |= KEY_A;
            key |= KEY_A;
            break;
	    case 'D':
        case 'd':
			if (key & KEY_D)
				key_held |= KEY_D;
            key |= KEY_D;
            break;
        case 'Q':
        case 'q':
			if (key & KEY_Q)
				key_held |= KEY_Q;
            key |= KEY_Q;
            break;
        case 'R':
        case 'r':
			if (key & KEY_R)
				key_held |= KEY_R;
            key |= KEY_R;
            break;
	    case 'S':
        case 's':
			if (key & KEY_S)
				key_held |= KEY_S;
            key |= KEY_S;
            break;
	    case 'W':
        case 'w':
			if (key & KEY_W)
				key_held |= KEY_W;
            key |= KEY_W;
            break;
	    case 'X':
        case 'x':
			if (key & KEY_X)
				key_held |= KEY_X;
            key |= KEY_X;
            break;
	    case 'Z':
        case 'z':
			if (key & KEY_Z)
				key_held |= KEY_Z;
            key |= KEY_Z;
            break;
		case '0':
			if (key & KEY_0)
				key_held |= KEY_0;
			key |= KEY_0;
			break;
		case '1':
			if (key & KEY_1)
				key_held |= KEY_1;
			key |= KEY_1;
			break;
		case '2':
			if (key & KEY_2)
				key_held |= KEY_2;
			key |= KEY_2;
			break;
		case '3':
			if (key & KEY_3)
				key_held |= KEY_3;
			key |= KEY_3;
			break;
		case '4':
			if (key & KEY_4)
				key_held |= KEY_4;
			key |= KEY_4;
			break;
		case '5':
			if (key & KEY_5)
				key_held |= KEY_5;
			key |= KEY_5;
			break;
		case '6':
			if (key & KEY_6)
				key_held |= KEY_6;
			key |= KEY_6;
			break;
		case '7':
			if (key & KEY_7)
				key_held |= KEY_7;
			key |= KEY_7;
			break;
		case '8':
			if (key & KEY_8)
				key_held |= KEY_8;
			key |= KEY_8;
			break;
		case '9':
			if (key & KEY_9)
				key_held |= KEY_9;
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
			key_held &= ~KEY_A;
            break;
	    case 'D':
        case 'd':
            key &= ~KEY_D;
			key_held &= ~KEY_D;
            break;
        case 'R':
        case 'r':
            key &= ~KEY_R;
			key_held &= ~KEY_R;
            break;
	    case 'S':
        case 's':
            key &= ~KEY_S;
			key_held &= ~KEY_S;
            break;
	    case 'W':
        case 'w':
            key &= ~KEY_W;
			key_held &= ~KEY_W;
            break;
	    case 'X':
        case 'x':
            key &= ~KEY_X;
			key_held &= ~KEY_X;
            break;
	    case 'Z':
        case 'z':
            key &= ~KEY_Z;
			key_held &= ~KEY_Z;
            break;
		case '0':
			key &= ~KEY_0;
			key_held &= ~KEY_0;
			break;
		case '1':
			key &= ~KEY_1;
			key_held &= ~KEY_1;
			break;
		case '2':
			key &= ~KEY_2;
			key_held &= ~KEY_2;
			break;
		case '3':
			key &= ~KEY_3;
			key_held &= ~KEY_3;
			break;
		case '4':
			key &= ~KEY_4;
			key_held &= ~KEY_4;
			break;
		case '5':
			key &= ~KEY_5;
			key_held &= ~KEY_5;
			break;
		case '6':
			key &= ~KEY_6;
			key_held &= ~KEY_6;
			break;
		case '7':
			key &= ~KEY_7;
			key_held &= ~KEY_7;
			break;
		case '8':
			key &= ~KEY_8;
			key_held &= ~KEY_8;
			break;
		case '9':
			key &= ~KEY_9;
			key_held &= ~KEY_9;
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

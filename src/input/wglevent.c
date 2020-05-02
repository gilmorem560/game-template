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
	
	#ifndef NDEBUG
	/* TODO: can uncapture mouse when debugging, need to display cursor too */
	if (debug_cursor_changed) {
		if (!mouse_captured)
			/* return visible cursor */
			ShowCursor(FALSE);
		else
			/* associate it */
			ShowCursor(TRUE);
		debug_cursor_changed = false;
	}
	#endif /* NDEBUG */
    
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
	RECT client_rect;
	printf("wndproc: ");
    switch (uMsg)
    {
	case WM_SIZE:
		#ifndef NDEBUG
		printf("WM_SIZE");
		#endif /* NDEBUG */
		GetClientRect(wnd, &client_rect);
		/* Keep OpenGL viewport in sync */
		glViewport(0, 0, (GLsizei) (client_rect.right - client_rect.left), (GLsizei) (client_rect.bottom - client_rect.top));
		break;
    case WM_KEYDOWN:
        #ifndef NDEBUG
        printf("WM_KEYDOWN\n");
        #endif /* NDEBUG */
        switch (wParam) {
	    case 'A':
        case 'a':
            key_pressed |= KEY_A;
            break;
	    case 'B':
        case 'b':
            key_pressed |= KEY_B;
            break;
		case 'C':
		case 'c':
			key_pressed |= KEY_C;
			break;
	    case 'D':
        case 'd':
            key_pressed |= KEY_D;
            break;
		case 'E':
		case 'e':
			key_pressed |= KEY_E;
			break;
		case 'F':
		case 'f':
			key_pressed |= KEY_F;
			break;
        case 'Q':
        case 'q':
            key_pressed |= KEY_Q;
            break;
        case 'R':
        case 'r':
            key_pressed |= KEY_R;
            break;
	    case 'S':
        case 's':
            key_pressed |= KEY_S;
            break;
		case 'T':
		case 't':
			key_pressed |= KEY_T;
			break;
		case 'V':
		case 'v':
			key_pressed |= KEY_V;
			break;
	    case 'W':
        case 'w':
            key_pressed |= KEY_W;
            break;
	    case 'X':
        case 'x':
            key_pressed |= KEY_X;
            break;
	    case 'Z':
        case 'z':
            key_pressed |= KEY_Z;
            break;
		case '0':
			key_pressed |= KEY_0;
			break;
		case '1':
			key_pressed |= KEY_1;
			break;
		case '2':
			key_pressed |= KEY_2;
			break;
		case '3':
			key_pressed |= KEY_3;
			break;
		case '4':
			key_pressed |= KEY_4;
			break;
		case '5':
			key_pressed |= KEY_5;
			break;
		case '6':
			key_pressed |= KEY_6;
			break;
		case '7':
			key_pressed |= KEY_7;
			break;
		case '8':
			key_pressed |= KEY_8;
			break;
		case '9':
			key_pressed |= KEY_9;
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
            key_pressed &= ~KEY_A;
            break;
	    case 'B':
        case 'b':
            key_pressed &= ~KEY_B;
            break;
		case 'C':
		case 'c':
			key_pressed &= ~KEY_C;
			break;
	    case 'D':
        case 'd':
            key_pressed &= ~KEY_D;
            break;
		case 'E':
		case 'e':
			key_pressed &= ~KEY_E;
			break;
		case 'F':
		case 'f':
			key_pressed &= ~KEY_F;
			break;
		case 'Q':
		case 'q':
			key_pressed &= ~KEY_Q;
			break;
        case 'R':
        case 'r':
            key_pressed &= ~KEY_R;
            break;
	    case 'S':
        case 's':
            key_pressed &= ~KEY_S;
            break;
		case 'T':
		case 't':
			key_pressed &= ~KEY_T;
			break;
		case 'V':
		case 'v':
			key_pressed &= ~KEY_V;
			break;
	    case 'W':
        case 'w':
            key_pressed &= ~KEY_W;
            break;
	    case 'X':
        case 'x':
            key_pressed &= ~KEY_X;
            break;
	    case 'Z':
        case 'z':
            key_pressed &= ~KEY_Z;
            break;
		case '0':
			key_pressed &= ~KEY_0;
			break;
		case '1':
			key_pressed &= ~KEY_1;
			break;
		case '2':
			key_pressed &= ~KEY_2;
			break;
		case '3':
			key_pressed &= ~KEY_3;
			break;
		case '4':
			key_pressed &= ~KEY_4;
			break;
		case '5':
			key_pressed &= ~KEY_5;
			break;
		case '6':
			key_pressed &= ~KEY_6;
			break;
		case '7':
			key_pressed &= ~KEY_7;
			break;
		case '8':
			key_pressed &= ~KEY_8;
			break;
		case '9':
			key_pressed &= ~KEY_9;
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

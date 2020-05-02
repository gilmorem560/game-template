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
			if (key_held & KEY_A)
				key_pressed &= ~KEY_A;
			else
				key_pressed |= KEY_A;
			key_held |= KEY_A;
			break;
	    case 'B':
        case 'b':
			if (key_held & KEY_B)
				key_pressed &= ~KEY_B;
			else
				key_pressed |= KEY_B;
			key_held |= KEY_B;
			break;
		case 'C':
		case 'c':
			if (key_held & KEY_C)
				key_pressed &= ~KEY_C;
			else
				key_pressed |= KEY_C;
			key_held |= KEY_C;
			break;
	    case 'D':
        case 'd':
			if (key_held & KEY_D)
				key_pressed &= ~KEY_D;
			else
				key_pressed |= KEY_D;
			key_held |= KEY_D;
			break;
		case 'E':
		case 'e':
			if (key_held & KEY_E)
				key_pressed &= ~KEY_E;
			else
				key_pressed |= KEY_E;
			key_held |= KEY_E;
			break;
		case 'F':
		case 'f':
			if (key_held & KEY_F)
				key_pressed &= ~KEY_F;
			else
				key_pressed |= KEY_F;
			key_held |= KEY_F;
			break;
        case 'Q':
        case 'q':
			if (key_held & KEY_Q)
				key_pressed &= ~KEY_Q;
			else
				key_pressed |= KEY_Q;
			key_held |= KEY_Q;
			break;
        case 'R':
        case 'r':
			if (key_held & KEY_R)
				key_pressed &= ~KEY_R;
			else
				key_pressed |= KEY_R;
			key_held |= KEY_R;
			break;
	    case 'S':
        case 's':
			if (key_held & KEY_S)
				key_pressed &= ~KEY_S;
			else
				key_pressed |= KEY_S;
			key_held |= KEY_S;
			break;
		case 'T':
		case 't':
			if (key_held & KEY_T)
				key_pressed &= ~KEY_T;
			else
				key_pressed |= KEY_T;
			key_held |= KEY_T;
			break;
		case 'V':
		case 'v':
			if (key_held & KEY_V)
				key_pressed &= ~KEY_V;
			else
				key_pressed |= KEY_V;
			key_held |= KEY_V;
			break;
	    case 'W':
        case 'w':
			if (key_held & KEY_W)
				key_pressed &= ~KEY_W;
			else
				key_pressed |= KEY_W;
			key_held |= KEY_W;
			break;
	    case 'X':
        case 'x':
			if (key_held & KEY_X)
				key_pressed &= ~KEY_X;
			else
				key_pressed |= KEY_X;
			key_held |= KEY_X;
			break;
	    case 'Z':
        case 'z':
			if (key_held & KEY_Z)
				key_pressed &= ~KEY_Z;
			else
				key_pressed |= KEY_Z;
			key_held |= KEY_Z;
			break;
		case '0':
			if (key_held & KEY_0)
				key_pressed &= ~KEY_0;
			else
				key_pressed |= KEY_0;
			key_held |= KEY_0;
			break;
		case '1':
			if (key_held & KEY_1)
				key_pressed &= ~KEY_1;
			else
				key_pressed |= KEY_1;
			key_held |= KEY_1;
			break;
		case '2':
			if (key_held & KEY_2)
				key_pressed &= ~KEY_2;
			else
				key_pressed |= KEY_2;
			key_held |= KEY_2;
			break;
		case '3':
			if (key_held & KEY_3)
				key_pressed &= ~KEY_3;
			else
				key_pressed |= KEY_3;
			key_held |= KEY_3;
			break;
		case '4':
			if (key_held & KEY_4)
				key_pressed &= ~KEY_4;
			else
				key_pressed |= KEY_4;
			key_held |= KEY_4;
			break;
		case '5':
			if (key_held & KEY_5)
				key_pressed &= ~KEY_5;
			else
				key_pressed |= KEY_5;
			key_held |= KEY_5;
			break;
		case '6':
			if (key_held & KEY_6)
				key_pressed &= ~KEY_6;
			else
				key_pressed |= KEY_6;
			key_held |= KEY_6;
			break;
		case '7':
			if (key_held & KEY_7)
				key_pressed &= ~KEY_7;
			else
				key_pressed |= KEY_7;
			key_held |= KEY_7;
			break;
		case '8':
			if (key_held & KEY_8)
				key_pressed &= ~KEY_8;
			else
				key_pressed |= KEY_8;
			key_held |= KEY_8;
			break;
		case '9':
			if (key_held & KEY_9)
				key_pressed &= ~KEY_9;
			else
				key_pressed |= KEY_9;
			key_held |= KEY_9;
			break;
		case ' ':
			if (key_held & KEY_SPACE)
				key_pressed &= ~KEY_SPACE;
			else
				key_pressed |= KEY_SPACE;
			key_held |= KEY_SPACE;
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
			key_held &= ~KEY_A;
            break;
	    case 'B':
        case 'b':
            key_pressed &= ~KEY_B;
			key_held &= ~KEY_B;
            break;
		case 'C':
		case 'c':
			key_pressed &= ~KEY_C;
			key_held &= ~KEY_C;
			break;
	    case 'D':
        case 'd':
            key_pressed &= ~KEY_D;
			key_held &= ~KEY_D;
            break;
		case 'E':
		case 'e':
			key_pressed &= ~KEY_E;
			key_held &= ~KEY_E;
			break;
		case 'F':
		case 'f':
			key_pressed &= ~KEY_F;
			key_held &= ~KEY_F;
			break;
		case 'Q':
		case 'q':
			key_pressed &= ~KEY_Q;
			key_held &= ~KEY_Q;
			break;
        case 'R':
        case 'r':
            key_pressed &= ~KEY_R;
			key_held &= ~KEY_R;
            break;
	    case 'S':
        case 's':
            key_pressed &= ~KEY_S;
			key_held &= ~KEY_S;
            break;
		case 'T':
		case 't':
			key_pressed &= ~KEY_T;
			key_held &= ~KEY_T;
			break;
		case 'V':
		case 'v':
			key_pressed &= ~KEY_V;
			key_held &= ~KEY_V;
			break;
	    case 'W':
        case 'w':
            key_pressed &= ~KEY_W;
			key_held &= ~KEY_W;
            break;
	    case 'X':
        case 'x':
            key_pressed &= ~KEY_X;
			key_held &= ~KEY_X;
            break;
	    case 'Z':
        case 'z':
            key_pressed &= ~KEY_Z;
			key_held &= ~KEY_Z;
            break;
		case '0':
			key_pressed &= ~KEY_0;
			key_held &= ~KEY_0;
			break;
		case '1':
			key_pressed &= ~KEY_1;
			key_held &= ~KEY_1;
			break;
		case '2':
			key_pressed &= ~KEY_2;
			key_held &= ~KEY_2;
			break;
		case '3':
			key_pressed &= ~KEY_3;
			key_held &= ~KEY_3;
			break;
		case '4':
			key_pressed &= ~KEY_4;
			key_held &= ~KEY_4;
			break;
		case '5':
			key_pressed &= ~KEY_5;
			key_held &= ~KEY_5;
			break;
		case '6':
			key_pressed &= ~KEY_6;
			key_held &= ~KEY_6;
			break;
		case '7':
			key_pressed &= ~KEY_7;
			key_held &= ~KEY_7;
			break;
		case '8':
			key_pressed &= ~KEY_8;
			key_held &= ~KEY_8;
			break;
		case '9':
			key_pressed &= ~KEY_9;
			key_held &= ~KEY_9;
			break;
		case ' ':
			key_pressed &= ~KEY_SPACE;
			key_held &= ~KEY_SPACE;
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

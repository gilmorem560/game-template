/*
 * glxinput - event processing for OpenGL in X11
 */
#include "input.h"
 
/*
 * glxevent - event processing for OpenGL in X11
 */
void glxevent(Display *dpy)
{
    XEvent event_return;

    if (XEventsQueued(dpy, QueuedAlready) == 0) {
        return;
    }
    
    /* immediately process any resize */
    if (XCheckWindowEvent(dpy, win, StructureNotifyMask, &event_return)) ;
	else
		XNextEvent(dpy, &event_return);

    #ifndef NDEBUG
    printf("XEvent: ");
    #endif /* NDEBUG */

    /* TODO: Suppprt more diverse input */
    switch (event_return.type) {
		case ConfigureNotify:
			#ifndef NDEBUG
            printf("ConfigureNotify\n");
            #endif /* NDEBUG */
			/* Keep OpenGL viewport in sync */
			glViewport(0, 0, (GLsizei) event_return.xconfigure.width, (GLsizei) event_return.xconfigure.height);
			break;
        case KeyPress:
            #ifndef NDEBUG
            printf("KeyPress\n");
            #endif /* NDEBUG */
            switch (XLookupKeysym(&event_return.xkey, 0)) {
                case XK_A:
                case XK_a:
					if (key & KEY_A)
						key_held |= KEY_A;
                    key |= KEY_A;
					break;
                case XK_D:
                case XK_d:
					if (key & KEY_D)
						key_held |= KEY_D;
                    key |= KEY_D;
					break;
                case XK_F:
                case XK_f:
					if (key & KEY_F)
						key_held |= KEY_F;
                    key |= KEY_F;
                    break;
				case XK_G:
                case XK_g:
					if (key & KEY_G)
						key_held |= KEY_G;
                    key |= KEY_G;
                    break;
                case XK_Q:
                case XK_q:
					if (key & KEY_Q)
						key_held |= KEY_Q;
                    key |= KEY_Q;
                    break;
                case XK_R:
                case XK_r:
					if (key & KEY_R)
						key_held |= KEY_R;
                    key |= KEY_R;
                    break;
                case XK_S:
                case XK_s:
					if (key & KEY_S)
						key_held |= KEY_S;
                    key |= KEY_S;
                    break;
				case XK_W:
                case XK_w:
					if (key & KEY_W)
						key_held |= KEY_W;
                    key |= KEY_W;
                    break;
				case XK_X:
                case XK_x:
					if (key & KEY_X)
						key_held |= KEY_X;
                    key |= KEY_X;
                    break;
				case XK_Z:
                case XK_z:
					if (key & KEY_Z)
						key_held |= KEY_Z;
                    key |= KEY_Z;
                    break;
				case XK_KP_0:
				case XK_0:
					if (key & KEY_0)
						key_held |= KEY_0;
					key |= KEY_0;
					break;
				case XK_KP_1:
				case XK_1:
					if (key & KEY_1)
						key_held |= KEY_1;
					key |= KEY_1;
					break;
				case XK_KP_2:
				case XK_2:
					if (key & KEY_2)
						key_held |= KEY_2;
					key |= KEY_2;
					break;
				case XK_KP_3:
				case XK_3:
					if (key & KEY_3)
						key_held |= KEY_3;
					key |= KEY_3;
					break;
				case XK_KP_4:
				case XK_4:
					if (key & KEY_4)
						key_held |= KEY_4;
					key |= KEY_4;
					break;
				case XK_KP_5:
				case XK_5:
					if (key & KEY_5)
						key_held |= KEY_5;
					key |= KEY_5;
					break;
				case XK_KP_6:
				case XK_6:
					if (key & KEY_6)
						key_held |= KEY_6;
					key |= KEY_6;
					break;
				case XK_KP_7:
				case XK_7:
					if (key & KEY_7)
						key_held |= KEY_7;
					key |= KEY_7;
					break;
				case XK_KP_8:
				case XK_8:
					if (key & KEY_8)
						key_held |= KEY_8;
					key |= KEY_8;
					break;
				case XK_KP_9:
				case XK_9:
					if (key & KEY_9)
						key_held |= KEY_9;
					key |= KEY_9;
					break;
                default:
                    break;
            }
            break;
        case KeyRelease:
            #ifndef NDEBUG
            printf("KeyRelease\n");
            #endif /* NDEBUG */
            switch (XLookupKeysym(&event_return.xkey, 0)) {
                case XK_A:
                case XK_a:
                    key &= ~KEY_A;
					key_held &= ~KEY_A;
                    break;
                case XK_D:
                case XK_d:
                    key &= ~KEY_D;
					key_held &= ~KEY_D;
                    break;
                case XK_F:
                case XK_f:
                    key &= ~KEY_F;
					key_held &= ~KEY_F;
                    break;
				case XK_G:
                case XK_g:
                    key &= ~KEY_G;
					key_held &= ~KEY_G;
                    break;
                case XK_R:
                case XK_r:
                    key &= ~KEY_R;
					key_held &= ~KEY_R;
                    break;
                case XK_S:
                case XK_s:
                    key &= ~KEY_S;
					key_held &= ~KEY_S;
                    break;
				case XK_W:
                case XK_w:
                    key &= ~KEY_W;
					key_held &= ~KEY_W;
                    break;
				case XK_X:
                case XK_x:
                    key &= ~KEY_X;
					key_held &= ~KEY_X;
                    break;
				case XK_Z:
                case XK_z:
                    key &= ~KEY_Z;
					key_held &= ~KEY_Z;
                    break;
				case XK_KP_0:
				case XK_0:
					key &= ~KEY_0;
					key_held &= ~KEY_0;
					break;
				case XK_KP_1:
				case XK_1:
					key &= ~KEY_1;
					key_held &= ~KEY_1;
					break;
				case XK_KP_2:
				case XK_2:
					key &= ~KEY_2;
					key_held &= ~KEY_2;
					break;
				case XK_KP_3:
				case XK_3:
					key &= ~KEY_3;
					key_held &= ~KEY_3;
					break;
				case XK_KP_4:
				case XK_4:
					key &= ~KEY_4;
					key_held &= ~KEY_4;
					break;
				case XK_KP_5:
				case XK_5:
					key &= ~KEY_5;
					key_held &= ~KEY_5;
					break;
				case XK_KP_6:
				case XK_6:
					key &= ~KEY_6;
					key_held &= ~KEY_6;
					break;
				case XK_KP_7:
				case XK_7:
					key &= ~KEY_7;
					key_held &= ~KEY_7;
					break;
				case XK_KP_8:
				case XK_8:
					key &= ~KEY_8;
					key_held &= ~KEY_8;
					break;
				case XK_KP_9:
				case XK_9:
					key &= ~KEY_9;
					key_held &= ~KEY_9;
					break;
                default:
                    break;
            }
            break;
        default:
			#ifndef NDEBUG
            printf("Unhandled\n");
            #endif /* NDEBUG */
            break;
    }
    
    return;
}

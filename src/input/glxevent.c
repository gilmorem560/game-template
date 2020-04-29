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
	XWindowAttributes current_attribs;
	XSetWindowAttributes new_attribs;
	int x_width, x_height;
	XGetWindowAttributes(dpy, win, &current_attribs);
	x_width = current_attribs.width;
	x_height = current_attribs.height;
	mouse_moved_x = false;
	mouse_moved_y = false;

	while (XEventsQueued(dpy, QueuedAlready) != 0) {
		/* immediately process any resize */
		if (XCheckWindowEvent(dpy, win, StructureNotifyMask, &event_return)) ;
		else
			XNextEvent(dpy, &event_return);

		#ifndef NDEBUG
		printf("XEvent: ");
		#endif /* NDEBUG */
		
		switch (event_return.type) {
			case MotionNotify:
				#ifndef NDEBUG
				printf("MotionNotify\n");
				printf("\tmouse_x: %d\n", event_return.xmotion.x);
				printf("\tmouse_y: %d\n", event_return.xmotion.y);
				#endif /* NDEBUG */
				if (event_return.xmotion.x != (x_width / 2)) {
					mouse_moved_x = true;
					mouse_x_positive = (event_return.xmotion.x > (x_width / 2)) ? true : false;
				}
				if (event_return.xmotion.y != (x_height / 2)) {
					mouse_moved_y = true;
					mouse_y_positive = (event_return.xmotion.y > (x_height / 2)) ? true : false;
				}

				#ifndef NDEBUG
				/* debuggers can uncapture the cursor */
				if (mouse_captured) {
				#endif /* NDEBUG */
					/* keep undelrying cursor in center of the screen */
					new_attribs.event_mask = current_attribs.your_event_mask &= ~PointerMotionMask;
					XChangeWindowAttributes(dpy, win, CWEventMask, &new_attribs);
					XWarpPointer(dpy, None, win, x_width / 2, x_height / 2, 0, 0, x_width / 2, x_height / 2);
					new_attribs.event_mask |= PointerMotionMask;
					XChangeWindowAttributes(dpy, win, CWEventMask, &new_attribs);
				#ifndef NDEBUG
				}
				#endif /* NDEBUG */
				break;
			case ConfigureNotify:
				#ifndef NDEBUG
				printf("ConfigureNotify\n");
				#endif /* NDEBUG */
				x_width = event_return.xconfigure.width;
				x_height = event_return.xconfigure.height;
				/* Keep OpenGL viewport in sync */
				glViewport(0, 0, (GLsizei) x_width, (GLsizei) x_height);
				current_ratio = x_width / x_height;
				
				#ifndef NDEBUG
				/* debuggers can uncapture the cursor */
				if (mouse_captured) {
				#endif /* NDEBUG */
					/* need to reposition cursor in the event of resizing */
					new_attribs.event_mask = current_attribs.your_event_mask &= ~PointerMotionMask;
					XChangeWindowAttributes(dpy, win, CWEventMask, &new_attribs);
					XWarpPointer(dpy, None, win, x_width / 2, x_height / 2, 0, 0, x_width / 2, x_height / 2);
					new_attribs.event_mask |= PointerMotionMask;
					XChangeWindowAttributes(dpy, win, CWEventMask, &new_attribs);
				#ifndef NDEBUG
				}
				#endif /* NDEBUG */
				break;
			case KeyPress:
				#ifndef NDEBUG
				printf("KeyPress\n");
				#endif /* NDEBUG */
				switch (XLookupKeysym(&event_return.xkey, 0)) {
					case XK_A:
					case XK_a:
						if (key_held & KEY_A)
							key_pressed &= ~KEY_A;
						else
							key_pressed |= KEY_A;
						key_held |= KEY_A;
						break;
					case XK_B:
					case XK_b:
						if (key_held & KEY_B)
							key_pressed &= ~KEY_B;
						else
							key_pressed |= KEY_B;
						key_held |= KEY_B;
						break;
					case XK_C:
					case XK_c:
						if (key_held & KEY_C)
							key_pressed &= ~KEY_C;
						else
							key_pressed |= KEY_C;
						key_held |= KEY_C;
						break;
					case XK_D:
					case XK_d:
						if (key_held & KEY_D)
							key_pressed &= ~KEY_D;
						else
							key_pressed |= KEY_D;
						key_held |= KEY_D;
						break;
					case XK_E:
					case XK_e:
						if (key_held & KEY_E)
							key_pressed &= ~KEY_E;
						else
							key_pressed |= KEY_E;
						key_held |= KEY_E;
						break;
					case XK_F:
					case XK_f:
						if (key_held & KEY_F)
							key_pressed &= ~KEY_F;
						else
							key_pressed |= KEY_F;
						key_held |= KEY_F;
						break;
					case XK_G:
					case XK_g:
						if (key_held & KEY_G)
							key_pressed &= ~KEY_G;
						else
							key_pressed |= KEY_G;
						key_held |= KEY_G;
						break;
					case XK_Q:
					case XK_q:
						if (key_held & KEY_Q)
							key_pressed &= ~KEY_Q;
						else
							key_pressed |= KEY_Q;
						key_held |= KEY_Q;
						break;
					case XK_R:
					case XK_r:
						if (key_held & KEY_R)
							key_pressed &= ~KEY_R;
						else
							key_pressed |= KEY_R;
						key_held |= KEY_R;
						break;
					case XK_S:
					case XK_s:
						if (key_held & KEY_S)
							key_pressed &= ~KEY_S;
						else
							key_pressed |= KEY_S;
						key_held |= KEY_S;
						break;
					case XK_T:
					case XK_t:
						if (key_held & KEY_T)
							key_pressed &= ~KEY_T;
						else
							key_pressed |= KEY_T;
						key_held |= KEY_T;
						break;
					case XK_V:
					case XK_v:
						if (key_held & KEY_V)
							key_pressed &= ~KEY_V;
						else
							key_pressed |= KEY_V;
						key_held |= KEY_V;
						break;
					case XK_W:
					case XK_w:
						if (key_held & KEY_W)
							key_pressed &= ~KEY_W;
						else
							key_pressed |= KEY_W;
						key_held |= KEY_W;
						break;
					case XK_X:
					case XK_x:
						if (key_held & KEY_X)
							key_pressed &= ~KEY_X;
						else
							key_pressed |= KEY_X;
						key_held |= KEY_X;
						break;
					case XK_Z:
					case XK_z:
						if (key_held & KEY_Z)
							key_pressed &= ~KEY_Z;
						else
							key_pressed |= KEY_Z;
						key_held |= KEY_Z;
						break;
					case XK_KP_0:
					case XK_0:
						if (key_held & KEY_0)
							key_pressed &= ~KEY_0;
						else
							key_pressed |= KEY_0;
						key_held |= KEY_0;
						break;
					case XK_KP_1:
					case XK_1:
						if (key_held & KEY_1)
							key_pressed &= ~KEY_1;
						else
							key_pressed |= KEY_1;
						key_held |= KEY_1;
						break;
					case XK_KP_2:
					case XK_2:
						if (key_held & KEY_2)
							key_pressed &= ~KEY_2;
						else
							key_pressed |= KEY_2;
						key_held |= KEY_2;
						break;
					case XK_KP_3:
					case XK_3:
						if (key_held & KEY_3)
							key_pressed &= ~KEY_3;
						else
							key_pressed |= KEY_3;
						key_held |= KEY_3;
						break;
					case XK_KP_4:
					case XK_4:
						if (key_held & KEY_4)
							key_pressed &= ~KEY_4;
						else
							key_pressed |= KEY_4;
						key_held |= KEY_4;
						break;
					case XK_KP_5:
					case XK_5:
						if (key_held & KEY_5)
							key_pressed &= ~KEY_5;
						else
							key_pressed |= KEY_5;
						key_held |= KEY_5;
						break;
					case XK_KP_6:
					case XK_6:
						if (key_held & KEY_6)
							key_pressed &= ~KEY_6;
						else
							key_pressed |= KEY_6;
						key_held |= KEY_6;
						break;
					case XK_KP_7:
					case XK_7:
						if (key_held & KEY_7)
							key_pressed &= ~KEY_7;
						else
							key_pressed |= KEY_7;
						key_held |= KEY_7;
						break;
					case XK_KP_8:
					case XK_8:
						if (key_held & KEY_8)
							key_pressed &= ~KEY_8;
						else
							key_pressed |= KEY_8;
						key_held |= KEY_8;
						break;
					case XK_KP_9:
					case XK_9:
						if (key_held & KEY_9)
							key_pressed &= ~KEY_9;
						else
							key_pressed |= KEY_9;
						key_held |= KEY_9;
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
						key_pressed &= ~KEY_A;
						key_held &= ~KEY_A;
						break;
					case XK_B:
					case XK_b:
						key_pressed &= ~KEY_B;
						key_held &= ~KEY_B;
						break;
					case XK_C:
					case XK_c:
						key_pressed &= ~KEY_C;
						key_held &= ~KEY_C;
						break;
					case XK_D:
					case XK_d:
						key_pressed &= ~KEY_D;
						key_held &= ~KEY_D;
						break;
					case XK_E:
					case XK_e:
						key_pressed &= ~KEY_E;
						key_held &= ~KEY_E;
						break;
					case XK_F:
					case XK_f:
						key_pressed &= ~KEY_F;
						key_held &= ~KEY_F;
						break;
					case XK_G:
					case XK_g:
						key_pressed &= ~KEY_G;
						key_held &= ~KEY_G;
						break;
					case XK_Q:
					case XK_q:
						key_pressed &= ~KEY_Q;
						key_held &= ~KEY_Q;
						break;
					case XK_R:
					case XK_r:
						key_pressed &= ~KEY_R;
						key_held &= ~KEY_R;
						break;
					case XK_S:
					case XK_s:
						key_pressed &= ~KEY_S;
						key_held &= ~KEY_S;
						break;
					case XK_T:
					case XK_t:
						key_pressed &= ~KEY_T;
						key_held &= ~KEY_T;
						break;
					case XK_V:
					case XK_v:
						key_pressed &= ~KEY_V;
						key_held &= ~KEY_V;
						break;
					case XK_W:
					case XK_w:
						key_pressed &= ~KEY_W;
						key_held &= ~KEY_W;
						break;
					case XK_X:
					case XK_x:
						key_pressed &= ~KEY_X;
						key_held &= ~KEY_X;
						break;
					case XK_Z:
					case XK_z:
						key_pressed &= ~KEY_Z;
						key_held &= ~KEY_Z;
						break;
					case XK_KP_0:
					case XK_0:
						key_pressed &= ~KEY_0;
						key_held &= ~KEY_0;
						break;
					case XK_KP_1:
					case XK_1:
						key_pressed &= ~KEY_1;
						key_held &= ~KEY_1;
						break;
					case XK_KP_2:
					case XK_2:
						key_pressed &= ~KEY_2;
						key_held &= ~KEY_2;
						break;
					case XK_KP_3:
					case XK_3:
						key_pressed &= ~KEY_3;
						key_held &= ~KEY_3;
						break;
					case XK_KP_4:
					case XK_4:
						key_pressed &= ~KEY_4;
						key_held &= ~KEY_4;
						break;
					case XK_KP_5:
					case XK_5:
						key_pressed &= ~KEY_5;
						key_held &= ~KEY_5;
						break;
					case XK_KP_6:
					case XK_6:
						key_pressed &= ~KEY_6;
						key_held &= ~KEY_6;
						break;
					case XK_KP_7:
					case XK_7:
						key_pressed &= ~KEY_7;
						key_held &= ~KEY_7;
						break;
					case XK_KP_8:
					case XK_8:
						key_pressed &= ~KEY_8;
						key_held &= ~KEY_8;
						break;
					case XK_KP_9:
					case XK_9:
						key_pressed &= ~KEY_9;
						key_held &= ~KEY_9;
						break;
					default:
						break;
				}
				break;
			default:
				#ifndef NDEBUG
				printf("Unhandled: %d\n", event_return.type);
				#endif /* NDEBUG */
				break;
		}
	}
    
    return;
}

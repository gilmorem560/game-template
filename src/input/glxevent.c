/*
 * glxinput - event processing for OpenGL in X11
 */
#include <stdio.h>
#include <assert.h>

#include "input.h"
 
/*
 * glxevent - event processing for OpenGL in X11
 */
void glxevent(Display *dpy)
{
    XEvent event_return;
    
    XNextEvent(dpy, &event_return);
    
    switch (event_return.type) {
        case KeyPress:
            #ifndef NDEBUG
            printf("KeyPress\n");
            #endif /* NDEBUG */
            switch (XLookupKeysym(&event_return.xkey, 0)) {
                case XK_M:
                case XK_m:
                    key |= KEY_M;
                    break;
                case XK_Q:
                case XK_q:
                    key |= KEY_Q;
                    break;
                case XK_R:
                case XK_r:
                    key |= KEY_R;
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
                case XK_M:
                case XK_m:
                    key &= ~KEY_M;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    return;
}

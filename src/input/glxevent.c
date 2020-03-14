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

    if (XEventsQueued(dpy, QueuedAlready) == 0) {
        keyHeld = 0;
        return;
    }
    
    XNextEvent(dpy, &event_return);

    #ifndef NDEBUG
    printf("XEvent: ");
    #endif /* NDEBUG */
    
    switch (event_return.type) {
        case Expose:
            #ifndef NDEBUG
            printf("Expose\n");
            #endif
            break;
        case KeyPress:
            #ifndef NDEBUG
            printf("KeyPress\n");
            key = 0;
            #endif /* NDEBUG */
            switch (XLookupKeysym(&event_return.xkey, 0)) {
                case XK_F:
                case XK_f:
                    key |= KEY_F;
                    break;
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
                case XK_S:
                case XK_s:
                    key |= KEY_S;
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
                case XK_F:
                case XK_f:
                    key &= ~KEY_F;
                    break;
                case XK_M:
                case XK_m:
                    key &= ~KEY_M;
                    break;
                case XK_R:
                case XK_r:
                    key &= ~KEY_R;
                    break;
                case XK_S:
                case XK_s:
                    key &= ~KEY_S;
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

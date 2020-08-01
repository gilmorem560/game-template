#ifndef __INPUT_H__
#define __INPUT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* configuration */
#ifndef _WIN32
#include "../../config.h"
#endif  /* _WIN32 */

/* OpenGL context */
#include "../graphics/contexts/glcontext.h"
  
/* key mask values */
#define KEY_Q       ((unsigned long) 1 << 0x00)
#define KEY_A       ((unsigned long) 1 << 0x01)
#define KEY_Z       ((unsigned long) 1 << 0x02)
#define KEY_W       ((unsigned long) 1 << 0x03)
#define KEY_S       ((unsigned long) 1 << 0x04)
#define KEY_X       ((unsigned long) 1 << 0x05)
#define KEY_E       ((unsigned long) 1 << 0x06)
#define KEY_D       ((unsigned long) 1 << 0x07)
#define KEY_C       ((unsigned long) 1 << 0x08)
#define KEY_R       ((unsigned long) 1 << 0x09)
#define KEY_F       ((unsigned long) 1 << 0x0A)
#define KEY_V       ((unsigned long) 1 << 0x0B)
#define KEY_T       ((unsigned long) 1 << 0x0C)
#define KEY_G       ((unsigned long) 1 << 0x0D)
#define KEY_B       ((unsigned long) 1 << 0x0E)
#define KEY_UP      ((unsigned long) 1 << 0x0F)
#define KEY_DOWN    ((unsigned long) 1 << 0x10)
#define KEY_LEFT    ((unsigned long) 1 << 0x11)
#define KEY_RIGHT   ((unsigned long) 1 << 0x12)
#define KEY_SPACE	((unsigned long) 1 << 0x13)
#define KEY_0       ((unsigned long) 1 << 0x14)
#define KEY_1       ((unsigned long) 1 << 0x15)
#define KEY_2       ((unsigned long) 1 << 0x16)
#define KEY_3       ((unsigned long) 1 << 0x17)
#define KEY_4       ((unsigned long) 1 << 0x18)
#define KEY_5       ((unsigned long) 1 << 0x19)
#define KEY_6       ((unsigned long) 1 << 0x1A)
#define KEY_7       ((unsigned long) 1 << 0x1B)
#define KEY_8       ((unsigned long) 1 << 0x1C)
#define KEY_9       ((unsigned long) 1 << 0x1D)

/* this is hacky... */
#define KEY_ISNUM(x)	x >> 0x13

/* key masks */
extern unsigned long key_pressed;
extern unsigned long key_held;

/* mouse state */
extern bool mouse_moved_x;
extern bool mouse_moved_y;
extern bool mouse_x_positive;
extern bool mouse_y_positive;

/* quit state */
extern bool quit;

#ifdef  _WIN32
/* wglevent - process WinAPI input */
extern void wglevent(HWND hWnd);
/* wndproc - main windows message processing loop */
extern LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#else
/* glxevent - process X11 input */
extern void glxevent(Display *dpy);
#endif  /* _WIN32 */

/* joypad support - linux and BSD only currently */
#ifdef HAVE_LIBEVDEV_LIBEVDEV_H
#include "joystick.h"
#endif
 
#ifndef NDEBUG
extern bool mouse_captured;
extern bool debug_cursor_changed;
#endif
    
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __INPUT_H__ */

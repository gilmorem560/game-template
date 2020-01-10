#ifndef __INPUT_H__
#define __INPUT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _WIN32
#include <X11/Xlib.h>   /* X11 libraries */
#include <X11/keysym.h> /* X11 key constants */
#else
#include <Windows.h>    /* WinAPI libraries */
#endif /* _WIN32 */
    
/* key mask values */
#define KEY_A       ((unsigned long) 1 << 0x00)
#define KEY_B       ((unsigned long) 1 << 0x01)
#define KEY_C       ((unsigned long) 1 << 0x02)
#define KEY_D       ((unsigned long) 1 << 0x03)
#define KEY_E       ((unsigned long) 1 << 0x04)
#define KEY_F       ((unsigned long) 1 << 0x05)
#define KEY_G       ((unsigned long) 1 << 0x06)
#define KEY_H       ((unsigned long) 1 << 0x07)
#define KEY_I       ((unsigned long) 1 << 0x08)
#define KEY_J       ((unsigned long) 1 << 0x09)
#define KEY_K       ((unsigned long) 1 << 0x0A)
#define KEY_L       ((unsigned long) 1 << 0x0B)
#define KEY_M       ((unsigned long) 1 << 0x0C)
#define KEY_N       ((unsigned long) 1 << 0x0D)
#define KEY_O       ((unsigned long) 1 << 0x0E)
#define KEY_P       ((unsigned long) 1 << 0x0F)
#define KEY_Q       ((unsigned long) 1 << 0x10)
#define KEY_R       ((unsigned long) 1 << 0x11)
#define KEY_S       ((unsigned long) 1 << 0x12)
#define KEY_T       ((unsigned long) 1 << 0x13)
#define KEY_U       ((unsigned long) 1 << 0x14)
#define KEY_V       ((unsigned long) 1 << 0x15)
#define KEY_W       ((unsigned long) 1 << 0x16)
#define KEY_X       ((unsigned long) 1 << 0x17)
#define KEY_Y       ((unsigned long) 1 << 0x18)
#define KEY_Z       ((unsigned long) 1 << 0x19)
#define KEY_UP      ((unsigned long) 1 << 0x1A)
#define KEY_DOWN    ((unsigned long) 1 << 0x1B)
#define KEY_LEFT    ((unsigned long) 1 << 0x1C)
#define KEY_RIGHT   ((unsigned long) 1 << 0x1D)
#define KEY_SPACE   ((unsigned long) 1 << 0x1E)
#define KEY_ENTER   ((unsigned long) 1 << 0x1F)

/* key masks */
unsigned long key;

#ifdef  _WIN32
/* wglevent - process WinAPI input */
void wglevent(HWND hWnd);
/* wndproc - main windows message processing loop */
LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#else
/* glxevent - process X11 input */
 void glxevent(Display *dpy);
#endif  /* _WIN32 */
    
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __INPUT_H__ */

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PAD_A 0
#define PAD_B 1
#define PAD_X 2
#define PAD_Y 3
#define PAD_START 4
#define PAD_SELECT 5
#define PAD_UP 6
#define PAD_DOWN 7
#define PAD_LEFT 8
#define PAD_RIGHT 9

extern unsigned long pad_pressed;
extern unsigned long pad_held;

extern void joystick_init(void);
extern void joystick_read(void);
extern void joystick_free(void);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __JOYSTICK_H__ */

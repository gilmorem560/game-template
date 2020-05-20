/*
 * input - general input properties and routines
 */
#include "input.h"

/* key masks */
unsigned long key_pressed;
unsigned long key_held;

/* mouse state */
bool mouse_moved_x;
bool mouse_moved_y;
bool mouse_x_positive;
bool mouse_y_positive;

/* quit state */
bool quit;

#ifndef NDEBUG
bool mouse_captured;
bool debug_cursor_changed;
#endif

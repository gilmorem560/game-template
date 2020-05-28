AC_INIT([game-template], [1.0], [segaloco@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects])
AC_PROG_CC
AC_PATH_X
AX_CHECK_GL
AX_CHECK_GLX
AC_CHECK_LIB([m],[sqrt])
AC_CHECK_LIB([evdev],[libevdev_new])
AC_CONFIG_HEADERS([config.h])
AC_CHECK_HEADERS_ONCE([fcntl.h unistd.h libevdev/libevdev.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT

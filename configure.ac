AC_INIT([OpenGL], [1.0], [segaloco@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR
AC_PATH_X
AX_CHECK_GL
AX_CHECK_GLX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/graphics/Makefile
    src/graphics/contexts/Makefile
    src/graphics/primitives/Makefile
    src/input/Makefile
])
AC_OUTPUT

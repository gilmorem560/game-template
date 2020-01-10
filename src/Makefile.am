SUBDIRS = graphics input

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = graphics/contexts/libglxcontext.a graphics/primitives/libprimitives.a input/libinput.a
main_LDFLAGS = @LIBS@ -lX11

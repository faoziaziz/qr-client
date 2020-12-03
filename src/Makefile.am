AM_CFLAGS = $(MORE_CFLAGS)
AM_CPPFLAGS = $(MORE_CPPFLAGS)
AM_LDFLAGS = $(MORE_LDFLAGS)

bin_PROGRAMS = cgenerator
dist_man_MANS = cgenerator.8

## TODO:5000 When you want to add more files, add them below.
## TODO:5000 Automake will find dependencies by itself. Run
## TODO:5000 ./autogen.sh after modifying this file.

cgenerator_SOURCES  = log.c log.h cgenerator.h cgenerator.c usb_set.h usb_set.c web_serv.c web_serv.h
cgenerator_CFLAGS   = $(AM_CFLAGS) @JANSSON_CFLAGS@
cgenerator_LDFLAGS  = $(AM_LDFLAGS) @JANSSON_LIBS@

## TODO:2004 Each time you have used `PKG_CHECK_MODULES` macro
## TODO:2004 in `configure.ac`, you get two variables that
## TODO:2004 you can substitute like above.

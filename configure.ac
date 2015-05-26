#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(GitBlocks, 0.7.3, tomolt@users.sourceforge.net)

AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX

# Checks for libraries & headers.
LT_INIT([dlopen])

WX_CFLAGS=`wx-config --version=2.8 --cflags`
WX_LIBS=`wx-config --version=2.8 --libs`
AC_SUBST(WX_CFLAGS)
AC_SUBST(WX_LIBS)

PKG_CHECK_MODULES([CB], [codeblocks])
AC_SUBST(CB_CFLAGS)
AC_SUBST(CB_LIBS)

cb_plugin_datadir="`$PKG_CONFIG codeblocks --variable sharedir`/codeblocks/"
cb_plugin_libdir="`$PKG_CONFIG codeblocks --variable libdir`/codeblocks/plugins/"
AC_SUBST([cb_plugin_datadir])
AC_SUBST([cb_plugin_libdir])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT


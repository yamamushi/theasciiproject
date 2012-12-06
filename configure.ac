AC_INIT([The ASCII Project], [0.1], [yamamushi@gmail.com], [TheASCIIProject], [http://www.theasciiproject.com/])
AC_PREREQ([2.59])

AC_CONFIG_AUX_DIR([m4])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.10 -Wall no-define color-tests])

AC_CONFIG_HEADERS([config.h])


AC_PROG_LIBTOOL

AC_PROG_GREP
AC_PROG_EGREP
AC_PROG_CXX

PKG_CHECK_MODULES([SDL], [sdl >= 1.2])
PKG_CHECK_MODULES([PNG], [libpng >= 1.2])
PKG_CHECK_MODULES([SQLITE], [sqlite3 >= 3.7.14])
BOOST_REQUIRE([1.52.0])


# Look for SDL_net
AC_CHECK_HEADER(SDL/SDL_ttf.h, , AC_MSG_ERROR([SDL_ttf header not found.]))
AC_CHECK_LIB(SDL_ttf, TTF_OpenFont, AC_SUBST([SDL_TTF_LIBS], [-lSDL_ttf]), AC_MSG_ERROR([Cannot find SDL_tff library.]), [${SDL_LIBS}])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT

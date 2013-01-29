AC_INIT([The ASCII Project], [0.1], [yamamushi@gmail.com], [TheASCIIProject], [http://www.theasciiproject.com/])
AC_PREREQ([2.59])

AC_CONFIG_AUX_DIR([m4])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.10 -Wall no-define color-tests])

AC_CONFIG_HEADERS([config.h])


AC_LANG_CPLUSPLUS
AC_PROG_LIBTOOL


AC_PROG_GREP
AC_PROG_EGREP
AC_PROG_CXX


# pkg-config checks
PKG_CHECK_MODULES([SDL], [sdl >= 1.2])
PKG_CHECK_MODULES([PNG], [libpng >= 1.2])
PKG_CHECK_MODULES([SQLITE], [sqlite3 >= 3.7.14])


# Boost Checks
BOOST_REQUIRE([1.52.0])

# Boost Header-Only Checks
BOOST_ASIO
BOOST_GEOMETRY

# Boost libraries that require linking.
BOOST_FILESYSTEM
BOOST_PROGRAM_OPTIONS
BOOST_SERIALIZATION
BOOST_THREADS



# Look for SDL_net
AC_CHECK_HEADER(SDL/SDL_ttf.h, , AC_MSG_ERROR([SDL_ttf header not found.]))
AC_CHECK_LIB(SDL_ttf, TTF_OpenFont, AC_SUBST([SDL_TTF_LIBS], [-lSDL_ttf]), AC_MSG_ERROR([Cannot find SDL_tff library.]), [${SDL_LIBS}])

AC_CHECK_HEADER(SDL/SDL_image.h, , AC_MSG_ERROR([SDL_image header not found.]))
AC_CHECK_LIB(SDL_image, main, AC_SUBST([SDL_IMAGE_LIBS], [-lSDL_image]), AC_MSG_ERROR([Cannot find SDL_image library.]), [${SDL_LIBS}])

AC_CHECK_HEADER(SDL/SDL_mixer.h, , AC_MSG_ERROR([SDL_mixer header not found.]))
AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio, AC_SUBST([SDL_MIXER_LIBS], [-lSDL_mixer]), AC_MSG_ERROR([Cannot find SDL_mixer library.]), [${SDL_LIBS}])

AC_CHECK_HEADER(SDL/SDL_gfxPrimitives.h, , AC_MSG_ERROR([SDL_gfx header not found.]))
AC_CHECK_LIB(SDL_gfx, zoomSurface, AC_SUBST([SDL_GFX_LIBS], [-lSDL_gfx]), AC_MSG_ERROR([Cannot find SDL_gfx library.]), [${SDL_LIBS}])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT

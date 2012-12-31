AUTOMAKE_OPTIONS = subdir-objects

aclocaldir = $(datadir)/aclocal
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -Im4

# We put boost_cppflags here as they apply across all targets
# Things are easier this way...
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(DEPS_CFLAGS) -I.
AM_LDFLAGS = $(BOOST_THREADS_LDFLAGS) $(BOOST_SIGNALS_LIBS)
# AM_LDFLAGS = -Wl,-rpath,. 
# AM_COLOR_TESTS=always
# DEPS_LIBS = $(BOOST_THREAD_LIBS)

aclocal_DATA = m4/boost.m4

bin_PROGRAMS = tap_server tap_client

tap_server_SOURCES = src/MainServer.cpp src/entities/Entity.cpp \
	src/mapping/EntityMap.cpp src/utils/ConsoleLog.cpp
tap_server_CPPFLAGS = -std=c++11 $(SQLITE_CFLAGS)
tap_server_LDADD = $(BOOST_THREAD_LIBS) $(BOOST_SERIALIZATION_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_FILESYSTEM_LIBS) $(SQLITE_LIBS)
# tap_server_LIBS = $(BOOST_THREAD_LIBS) $(BOOST_SERIALIZATION_LIBS)

tap_client_SOURCES = src/MainClient.cpp src/io/SelfPath.cpp src/graphics/ClientWindow.cpp \
	src/graphics/BitmapFont.cpp src/graphics/Window.cpp src/audio/Mixer.cpp \
	src/graphics/Frame.cpp src/graphics/widget/Widget.cpp src/io/ClientKeyboard.cpp \
	src/graphics/widget/FadeAnimation.cpp src/utils/Timer.cpp src/graphics/Pixels.cpp \
	src/io/Mouse.cpp src/graphics/SDL_Resize.cpp src/graphics/widget/Button.cpp
tap_client_CPPFLAGS = -std=c++11 $(SDL_CFLAGS) $(PNG_CFLAGS) $(SDL_TTF_CFLAGS) $(BOOST_CPPFLAGS) 
tap_client_LDFLAGS = -Wl,-rpath,. 
tap_client_LDADD = $(BOOST_THREAD_LIBS) $(BOOST_SERIALIZATION_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_FILESYSTEM_LIBS) $(SDL_LIBS) $(SDL_TTF_LIBS) $(SDL_IMAGE_LIBS) $(SDL_MIXER_LIBS) $(SDL_GFX_LIBS)
# tap_client_LIBS = $(BOOST_THREAD_LIBS) $(BOOST_SERIALIZATION_LIBS)


dist_noinst_SCRIPTS = autogen.sh

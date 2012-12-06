AUTOMAKE_OPTIONS = subdir-objects

aclocaldir = $(datadir)/aclocal
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -Im4
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(DEPS_CFLAGS) -std=c++11 -I.
AM_LDFLAGS = $(BOOST_THREADS_LDFLAGS)
AM_COLOR_TESTS=always
DEPS_LIBS = $(BOOST_THREAD_LIBS)

aclocal_DATA = m4/boost.m4

bin_PROGRAMS = tap_server tap_client

tap_server_SOURCES = src/MainServer.cpp src/entities/Entity.cpp src/entities/Entity.h \
	src/mapping/EntityMap.cpp src/mapping/EntityMap.h
tap_server_CPPFLAGS = $(BOOST_CPPFLAGS)
tap_server_LDFLAGS = $(SQLITE_CFLAGS) $(BOOST_THREAD_LDFLAGS)
tap_server_LIBS = $(BOOST_THREAD_LIBS)

tap_client_SOURCES = src/MainClient.cpp
tap_client_CPPFLAGS = $(BOOST_CPPFLAGS)
tap_client_LDFLAGS = $(SDL_CFLAGS) $(PNG_CFLAGS) $(BOOST_THREAD_LDFLAGS)
tap_client_LIBS = $(BOOST_THREAD_LIBS)


dist_noinst_SCRIPTS = autogen.sh

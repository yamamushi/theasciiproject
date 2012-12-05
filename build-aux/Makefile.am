AUTOMAKE_OPTIONS = subdir-objects

aclocaldir = $(datadir)/aclocal
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(DEPS_CFLAGS) -std=c++11 -I.
AM_LDFLAGS = $(BOOST_THREADS_LDFLAGS)
AM_COLOR_TESTS=always
LIBS = $(BOOST_THREAD_LIBS)

aclocal_DATA = boost.m4

bin_PROGRAMS = tap_server
tap_server_SOURCES = ../src/MainServer.cc ../src/entities/Entity.cc ../src/entities/Entity.h \ 
	../src/mapping/EntityMap.cc ../src/mapping/EntityMap.h
tap_server_LDADD = $(DEPS_LIBS)

dist_noinst_SCRIPTS = ../autogen.sh

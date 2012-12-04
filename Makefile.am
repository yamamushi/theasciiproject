AUTOMAKE_OPTIONS = subdir-objects

aclocaldir = $(datadir)/aclocal
ACLOCAL_AMFLAGS = -I. ${ACLOCAL_FLAGS}
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(DEPS_CFLAGS) -std=c++11 
AM_LDFLAGS = $(BOOST_THREADS_LDFLAGS)
LIBS = $(BOOST_THREAD_LIBS)

aclocal_DATA = boost.m4

bin_PROGRAMS = tap_server
tap_server_SOURCES = src/MainServer.cc src/entities/Entity.cc src/entities/Entity.h
tap_server_LDADD = $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh

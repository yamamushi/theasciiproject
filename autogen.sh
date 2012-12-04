#!/bin/sh -e

test -n "$srcdir/build-aux" || srcdir=`dirname "$0/build-aux"`
test -n "$srcdirf" || srcdir=./build-aux
autoreconf --force --install --verbose "$srcdir"
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"

make -k

mv tap_server bin/

make distclean

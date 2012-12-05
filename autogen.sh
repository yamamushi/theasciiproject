#!/bin/sh -e

test -n "$srcdir/build-aux" || srcdir=`dirname "$0/build-aux"`
test -n "$srcdirf" || srcdir=./build-aux
autoreconf --force --install --verbose "$srcdir"
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"

make -k

## Leaving this out to allow for "make install" to work properly
# mv tap_server bin/

## Uncomment to get a clean build process
# make distclean

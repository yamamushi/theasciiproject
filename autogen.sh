#!/bin/sh -e

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
autoreconf --force --install --verbose "$srcdir"
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"

make -k

## Leave this out to allow for "make install" to work properly
mv tap_server bin/
mv tap_client bin/
## Uncomment to get a clean build process
./clean.sh

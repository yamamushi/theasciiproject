#!/bin/bash

make distclean

rm ./aclocal.m4
rm -rf ./autom4te.cache
rm ./configure
rm ./config.h*
rm ./Makefile.in

rm ./m4/config.*
rm ./m4/depcomp
rm ./m4/install-sh
rm ./m4/l*
rm ./m4/missing

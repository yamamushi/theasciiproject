SRCDIR=./src
INCDIR=./include
BUILDDIR=./build
CFLAGS=$(FLAGS) -I$(INCDIR) -I$(SRCDIR) -Wall
CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -o $(BUILDDIR)/$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

CPP_OBJS=main.o

all : main

main : $(CPP_OBJS)
	$(CPP) $(BUILDDIR)/$(CPP_OBJS) -o $@ -ltcod -ltcodxx -Wl,-rpath,.

clean :
	\rm -f $(BUILDDIR)/$(CPP_OBJS) main

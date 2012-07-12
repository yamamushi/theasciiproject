SRCDIR=./src
INCDIR=./include
LIBTCOD=./include/libtcod
BUILDDIR=./build/
CFLAGS=$(FLAGS) -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall
CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

CPP_OBJS=Main.o Tiles.o TileMap.o Entities.o EntityMap.o \
     Dungeon.o Keyboard.o Graphics.o

all : client

client : $(CPP_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CPP_OBJS)) -o $@ -ltcod -Wl,-rpath,.

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CPP_OBJS)) client

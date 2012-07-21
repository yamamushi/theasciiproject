SRCDIR=./src
INCDIR=./include
LIBTCOD=./include/libtcod
BUILDDIR=./build/
CFLAGS=$(FLAGS) -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall
CFLAGS += -D_VERSION='"2.3.9.7"' -DMACOSX
CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

CPP_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
    FovLib.o Dungeon.o Keyboard.o RenderMap.o \
    ClientMap.o Graphics.o Main.o

all : client

client : $(CPP_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CPP_OBJS)) -o ./bin/$@ -lSockets -ltcod -Wl,-rpath,. -lpthread

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CPP_OBJS)) ./bin/*

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
    DisplaySocket.o ClientMap.o Graphics.o

all : client server

client : $(CPP_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CPP_OBJS) Main_Client.o) -o ./bin/$@ -lSockets -lssl -lcrypto -ltcod -Wl,-rpath,. -lpthread

server : $(CPP_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CPP_OBJS) Main_Server.o) -o ./bin/$@ -lSockets -lssl -lcrypto -ltcod -Wl,-rpath,. -lpthread

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CPP_OBJS)) ./bin/*

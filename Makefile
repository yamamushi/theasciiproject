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
	$(CC) $(CFLAGS) -o $(BUILDDIR)$@ -c $<

CLIENT_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
    FovLib.o Dungeon.o Keyboard.o RenderMap.o tpl.o \
    NetworkLib.o ClientSocket.o ClientMap.o Graphics.o \
    Serialization.o Main_Client.o

SERVER_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
    FovLib.o Dungeon.o Keyboard.o RenderMap.o tpl.o \
    NetworkLib.o ServerSocket.o ClientMap.o Graphics.o \
    Serialization.o Main_Server.o

all : client server

client : $(CLIENT_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CLIENT_OBJS)) -o ./bin/$@ -lSockets -lssl -lcrypto -ltcod -Wl,-rpath,. -lpthread

server : $(SERVER_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(SERVER_OBJS)) -o ./bin/$@ -lSockets -lssl -lcrypto -ltcod -Wl,-rpath,. -lpthread

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CLIENT_OBJS) $(SERVER_OBJS)) ./bin/*

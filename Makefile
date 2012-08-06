SRCDIR=./src
INCDIR=./include
LIBTCOD=./include/libtcod
BUILDDIR=./build/
CFLAGS=$(FLAGS) -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall -Wswitch
CPPFLAGS=$(FLAGS) -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall -Wswitch -std=c++11
CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)$@ -c $<

CLIENT_OBJS= tpl.o ClientSocket.o ClientMap.o Graphics.o \
    Keyboard.o Serialization.o Main_Client.o

SERVER_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
    FovLib.o Dungeon.o Keyboard.o RenderMap.o tpl.o \
    ServerSocket.o ClientSocket.o ClientMap.o Graphics.o \
	Collect.o Serialization.o Main_Server.o

all : client server

client : $(CLIENT_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CLIENT_OBJS)) -o ./bin/$@ -lssl -lcrypto -ltcod -ltcodxx -Wl,-rpath,. -lpthread -lssl -lcrypto -lboost_system -lboost_thread

server : $(SERVER_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(SERVER_OBJS)) -o ./bin/$@ -lssl -lcrypto -ltcod -ltcodxx -Wl,-rpath,. -lpthread -lssl -lcrypto -lboost_system -lboost_thread

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CLIENT_OBJS) $(SERVER_OBJS))

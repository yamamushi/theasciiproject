UNAME:=$(shell uname)

SRCDIR=./src
INCDIR=./include
INCTCOD=./include/libtcod
BUILDDIR=./build/

ifeq ($(UNAME),MINGW32_NT-6.1)
	LIBSSL=/usr/local/ssl/lib
	LIBTCOD=./windows
	LIBBOOST=/c/Boost/lib
	INCBOOST=/c/Boost/include/boost-1_50
	
	CFLAGS=$(FLAGS) -D TPL_NOLIB -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -I$(INCBOOST) -w -Wswitch
	CPPFLAGS=$(FLAGS) -D TPL_NOLIB -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -I$(INCBOOST) -w -Wswitch -std=c++11

	LDLIB=-ltcod-mingw -lboost_system-mgw47-1_50 -lboost_thread-mgw47-mt-1_50 -L$(LIBBOOST) -L$(LIBSSL) -L$(LIBTCOD) -lws2_32
else
	CFLAGS=$(FLAGS) -I$(INCTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall -Wswitch
	CPPFLAGS=$(FLAGS) -I$(INCTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall -Wswitch -std=c++11
	
	LDLIB=-ltcod -ltcodxx -lboost_system -lboost_thread
endif

CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)$@ -c $<
	
CLIENT_OBJS=tpl.o ClientSocket.o ClientMap.o Graphics.o \
    Keyboard.o Serialization.o Main_Client.o

SERVER_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
    FovLib.o Dungeon.o Keyboard.o RenderMap.o tpl.o \
    ServerSocket.o ClientSocket.o ClientMap.o Graphics.o \
	Collect.o Serialization.o Main_Server.o
	
ifeq ($(UNAME),MINGW32_NT-6.1)
CLIENT_OBJS:=nonempty.o mmap.o $(CLIENT_OBJS)
SERVER_OBJS:=nonempty.o mmap.o $(SERVER_OBJS)
endif

all : client server

client : $(CLIENT_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CLIENT_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

server : $(SERVER_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(SERVER_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

ifeq ($(UNAME),MINGW32_NT-6.1)
mmap.o:
	$(CC) -o $(BUILDDIR)mmap.o -c include/win/mmap.c
	
nonempty.o:
	$(CC) -o $(BUILDDIR)nonempty.o -c include/win/nonempty.c
endif

clean :
	rm -f $(addprefix $(BUILDDIR), $(CLIENT_OBJS) $(SERVER_OBJS))

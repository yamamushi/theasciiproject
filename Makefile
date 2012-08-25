UNAME:=$(shell uname)

SRCDIR=./src
INCDIR=./include
INCTCOD=./include/libtcod
BUILDDIR=./build/
CFLAGS=$(FLAGS) -I$(INCTCOD) -I$(INCDIR) -I$(SRCDIR) -w #-Wall -Wswitch
CPPFLAGS=$(FLAGS) -I$(INCTCOD) -I$(INCDIR) -I$(SRCDIR) -w -std=c++11 #-Wall -Wswitch -std=c++11

LIBWIN=./windows

ifeq ($(UNAME),MINGW32_NT-6.1)
	LIBSSL=/usr/local/ssl/lib
	INCBOOST=/c/Boost/include/boost-1_50
	
	CFLAGS:=-D TPL_NOLIB -I$(INCBOOST) $(CFLAGS)
	CPPFLAGS:=-D TPL_NOLIB -I$(INCBOOST) $(CPPFLAGS)

	LDLIB=-ltcod-mingw -ltcod-gui-mingw -lboost_system-mgw47-1_50 -lboost_thread-mgw47-mt-1_50 -L$(LIBSSL) -L$(LIBWIN) -lws2_32
else	
	LDLIB=-ltcod -ltcodxx -lboost_system -lboost_thread -lpqxx -lpq -lboost_program_options -lboost_filesystem -lboost_serialization -lboost_regex
endif

CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)$@ -c $<
	
CLIENT_OBJS=tpl.o ClientWidgets.o ClientSocket.o ClientMap.o Graphics.o \
    Keyboard.o Serialization.o Main_Client.o

SERVER_OBJS=NetworkLib.o Tiles.o TileMap.o Entities.o EntityMap.o \
        FovLib.o Dungeon.o RenderMap.o tpl.o \
        ServerSocket.o ClientSocket.o ClientMap.o Graphics.o \
        DBConnector.o WorldMap.o Collect.o Serialization.o Main_Server.o

all : client server

#Windows start
win-all: win-client win-server

win-client: nonempty.o mmap.o $(CLIENT_OBJS)
	$(CPP) $(BUILDDIR)mmap.o $(BUILDDIR)nonempty.o $(addprefix $(BUILDDIR), $(CLIENT_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)
	cp $(LIBWIN)/*.dll ./bin/
	cp -r ./data ./bin/

win-server: $(SERVER_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(SERVER_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)
	
mmap.o:
	$(CC) -o $(BUILDDIR)mmap.o -c include/win/mmap.c
	
nonempty.o:
	$(CC) -o $(BUILDDIR)nonempty.o -c include/win/nonempty.c
#Windows end

client : $(CLIENT_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CLIENT_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

server : $(SERVER_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(SERVER_OBJS)) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

clean :
	rm -f $(addprefix $(BUILDDIR), $(CLIENT_OBJS) $(SERVER_OBJS)) $(BUILDDIR)*.o

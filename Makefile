UNAME:=$(shell uname)

SRCDIR=./src
INCDIR=./include
INCTCOD=./include/libtcod
BUILDDIR=./build
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
	LDLIB=-lstdc++ -lpthread -ltcodgui -ltcod -ltcodxx -lboost_system -lboost_thread -lpqxx -lpq -lboost_program_options -lboost_filesystem -lboost_serialization -lboost_regex
	#/usr/local/lib/libboost_system.a /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_program_options.a /usr/local/lib/libboost_filesystem.a /usr/local/lib/libboost_serialization.a /usr/local/lib/libboost_regex.a
endif

CC=gcc
CPP=g++

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

CLIENT_OBJS_FILES=tpl.o ClientWidgets.o ClientSocket.o ClientMap.o Graphics.o \
    Keyboard.o Serialization.o NetworkLib.o Platform.o ui_input.o Main_Client.o

SERVER_OBJS_FILES=NetworkLib.o Tiles.o TileMap.o Entities.o EntityMap.o \
        FovLib.o Dungeon.o RenderMap.o tpl.o InputParser.o FunctionUtils.o \
        ServerSocket.o ClientMap.o ConfigParser.o MapHandler.o Scene.o \
        DBConnector.o WorldMap.o Collect.o Serialization.o Main_Server.o

CLIENT_OBJS=$(addprefix $(BUILDDIR)/, $(CLIENT_OBJS_FILES))
SERVER_OBJS=$(addprefix $(BUILDDIR)/, $(SERVER_OBJS_FILES))

all : client server

#Windows start
win-all: win-client win-server

win-client: nonempty.o mmap.o $(CLIENT_OBJS)
	$(CPP) $(BUILDDIR)/mmap.o $(BUILDDIR)/nonempty.o $(CLIENT_OBJS) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)
	cp $(LIBWIN)/*.dll ./bin/
	cp -r ./data ./bin/

win-server: $(SERVER_OBJS)
	$(CPP) $(SERVER_OBJS) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

mmap.o:
	$(CC) -o $(BUILDDIR)/mmap.o -c include/win/mmap.c

nonempty.o:
	$(CC) -o $(BUILDDIR)/nonempty.o -c include/win/nonempty.c
#Windows end

client : $(CLIENT_OBJS)
	$(CPP) $(CLIENT_OBJS) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

server : $(SERVER_OBJS)
	$(CPP) $(SERVER_OBJS) -o ./bin/$@ -lssl -lcrypto -Wl,-rpath,. -lpthread -lssl -lcrypto $(LDLIB)

clean :
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(BUILDDIR)/*.o

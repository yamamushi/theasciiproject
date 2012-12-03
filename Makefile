UNAME:=$(shell uname)

SRCDIR=./src
INCDIR=./include
BUILDDIR=./build
CFLAGS=$(FLAGS) -I$(INCDIR) -I$(SRCDIR) -w #-Wall -Wswitch
CPPFLAGS=$(FLAGS) -I$(INCDIR) -I$(SRCDIR) -w -std=c++11 #-Wall -Wswitch -std=c++11

LDLIB=-lstdc++ 

CC=gcc
CPP=g++

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

SERVER_OBJS_FILES=main_server.o

SERVER_OBJS=$(addprefix $(BUILDDIR)/, $(ENGINE_OBJS_FILES))

CLIENT_OBJS_FILES=main_client.o

CLIENT_OBJS=$(addprefix $(BUILDDIR)/, $(CLIENT_OBJS_FILES))

ENGINE_OBJS_FILES=main_engine.o

ENGINE_OBJS=$(addprefix $(BUILDDIR)/, $(CLIENT_OBJS_FILES))






all : server client

server : $(SERVER_OBJS)
	$(CPP) $(SERVER_OBJS) -o ./bin/$@ -Wl,-rpath,. $(LDLIB)

client : $(CLIENT_OBJS)
	$(CPP) $(CLIENT_OBJS) -o ./bin/$@ -Wl,-rpath,. $(LDLIB)

engine : $(ENGINE_OBJS)
	$(CPP) $(ENGINE_OBJS) -o ./bin/$@ -Wl,-rpath,. $(LDLIB)



clean :
	rm -f $(BUILDDIR)/*.o


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

ENGINE_OBJS_FILES=Main.o

ENGINE_OBJS=$(addprefix $(BUILDDIR)/, $(ENGINE_OBJS_FILES))

all : engine

engine : $(ENGINE_OBJS)
	$(CPP) $(ENGINE_OBJS) -o ./bin/$@ -Wl,-rpath,. $(LDLIB)

clean : 
	rm -f $(BUILDDIR)/*.o


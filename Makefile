SRCDIR=./src
INCDIR=./include
LIBTCOD=./include/libtcod
BUILDDIR=./build/
CXXFLAGS=$(FLAGS) -I$(LIBTCOD) -I$(INCDIR) -I$(SRCDIR) -Wall -g3 -gdwarf-2
CC=gcc
CPP=g++
.SUFFIXES: .o .h .c .hpp .cpp

%.o : $(SRCDIR)/%.cpp
	$(CPP) $(CXXFLAGS) -o $(BUILDDIR)$@ -c $<
%.o : $(SRCDIR)/%.c
	$(CC) $(CXXFLAGS) -o $@ -c $<

CPP_OBJS=Tiles.o TileMap.o Entities.o EntityMap.o \
     Dungeon.o Keyboard.o Graphics.o Main.o

all : client

client : $(CPP_OBJS)
	$(CPP) $(addprefix $(BUILDDIR), $(CPP_OBJS)) -o $@ -ltcod -ltcodxx -Wl,-rpath,.

clean :
	\rm -f $(addprefix $(BUILDDIR), $(CPP_OBJS)) client

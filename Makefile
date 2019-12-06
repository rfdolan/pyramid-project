#
# Makefile for pyramid game
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#

# Compiler.
CC= g++ 

# Libraries and includes.
LINKDIR= -L../dragonfly/lib # path to dragonfly library
INCDIR= -I../dragonfly/include # path to dragonfly includes

## Uncomment and update below if using local SFML installation.
LINKDIR:= $(LINKDIR) -L$(HOME)/src/SFML/lib 
INCDIR:= $(INCDIR) -I$(HOME)/src/SFML/include

### Uncomment only 1 of the below! ###

# 1) Uncomment below for Linux (64-bit).
CFLAGS= -Wall
LINKLIB= -ldragonfly-linux64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

# 2) Uncomment below for Mac (64-bit).
# Note: if homebrew install sfml, may be in:
#   /usr/local/Cellar/sfml
#CFLAGS=
#LINKLIB= -ldragonfly-mac64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

######

## Engine options

# Uncomment below if using std::vector<Object *> instead of ObjectList.
#CFLAGS:= $(CFLAGS) -DUSE_STL

# Uncomment below if registerInterest() is defined in engine.
CFLAGS:= $(CFLAGS) -DDF_REGISTER_INTEREST

######

CC= g++ 
GAMESRC= Ankh.cpp \
	AnkhTimer.cpp \
	Exit.cpp \
	Health.cpp \
	Hero.cpp \
	Timer.cpp \
	Wall.cpp \
        Mummy.cpp \

GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)
DEBUG=
CFLAGS:= $(CFLAGS) $(DEBUG)

all: $(SRC) $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $(INCDIR) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
# DO NOT DELETE

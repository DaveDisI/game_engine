OS := $(shell uname -s)
CC=g++
FLAGS=-Wall -std=c++11
CFLAGS=-Wall -std=c++11 -c
OUT=-o ./bin/output_bin
INC=-I ./include
CINC=-I ../../include
SRC=./src/main.cpp
OBJ=../../src/io_manager.cpp \
    ../../src/render_manager.cpp \
		../../src/text_renderer.cpp \
		../../src/game_math.cpp

ifeq ($(OS), Darwin)
	LIBLOC=-L ./lib/mac/
	CLIBLOC=-L ../lib/mac
	LIB=-lSDL2 -lGLEW -lfreetype -lz -lbz2
	FWLOC=-F ./lib/mac/
	CFWLOC=-F../lib/mac/
	FW=-framework cocoa -framework IOKit -framework CoreVideo -framework AudioToolbox -framework CoreAudio \
	   -framework OpenGL -framework ForceFeedback -framework Carbon -framework Metal
	OBJLOC=obj/mac
endif



all:
	$(CC) $(FLAGS) $(OUT) $(SRC) $(OBJLOC)/*.o $(INC) $(LIBLOC) $(LIB) $(FWLOC) $(FW)

compile:
	cd $(OBJLOC); $(CC) $(CFLAGS) $(OBJ) $(CINC)

iomgr:
	cd $(OBJLOC); $(CC) $(CFLAGS) ../../src/io_manager.cpp $(CINC)

rdrmgr:
		cd $(OBJLOC); $(CC) $(CFLAGS) ../../src/render_manager.cpp $(CINC)

txtrdr:
		cd $(OBJLOC); $(CC) $(CFLAGS) ../../src/text_renderer.cpp $(CINC)

gmath:
		cd $(OBJLOC); $(CC) $(CFLAGS) ../../src/game_math.cpp $(CINC)

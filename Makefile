INCLUDE_PATH = -IC:\msys64\mingw64\include\SDL2
LIB_PATH = -LC:\msys64\mingw64\lib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
FLAGS = -w -Wl,-subsystem,windows

SDL = $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(LIBS)
BIN_DIR = bin

.PHONY: all clean

all: mini

mini: $(BIN_DIR)/mini

$(BIN_DIR)/mini: src/mini.cpp
	g++ $< $(SDL) -o $@

clean:
	rm -f $(BIN_DIR)/*

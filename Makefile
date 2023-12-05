INCLUDE_PATH = -IC:\msys64\mingw64\include\SDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIB_PATH = -LC:\msys64\mingw64\lib
LIBS = -lmingw32 -lSDL2main -lSDL2
FLAGS = -w -Wl,-subsystem,windows

SDL = $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(LIBS)

all: menu direccion bfg manager

menu: src/menu_img.cpp
	g++ $< $(SDL) -o bin/$@

m: menu
	./bin/menu

direccion: src/direccion.cpp
	g++ $< $(SDL) -o bin/$@

d: direccion
	./bin/direccion

bfg: src/bfg.cpp
	g++ $< $(SDL) -o bin/$@

b: bfg
	./bin/bfg

mapa: src/mapa.cpp
	g++ $< $(SDL) -o bin/$@

map: mapa
	./bin/mapa


main: src/main.cpp
	g++ $< $(SDL) -o bin/$@

mai: main
	./bin/main
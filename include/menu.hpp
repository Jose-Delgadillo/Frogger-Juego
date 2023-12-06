
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_TOTAL
};

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
extern SDL_Surface* gCurrentSurface;

// Enumera las opciones del menú
enum MenuOption
{
    MENU_OPTION_START,
    MENU_OPTION_EXIT
};

// Estructura para representar las opciones del menú
struct MenuItem
{
    SDL_Surface* surface;  // Imagen para la opción
};

class Menu
{
public:
    void handleEvents(SDL_Event& e);

private:
    bool quit_ = false;  // Variable de control para salir
};

// Muestra el menú y devuelve la opción seleccionada por el usuario
int showMenu(SDL_Surface* gScreenSurface, MenuItem menuItems[], int itemCount);

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

#endif // MENU_H

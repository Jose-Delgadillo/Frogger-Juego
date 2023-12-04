#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

class SDLManager
{
public:
    SDLManager();
    ~SDLManager();

    bool init();
    bool loadMedia();
    void close();

    void handleEvents();
    void render();
    SDL_Surface* loadSurface(std::string path);
    bool getQuitStatus() const { return quit; }

private:
    SDL_Window *gWindow;
    SDL_Surface *gScreenSurface;
    SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
    SDL_Surface *gCurrentSurface;
    bool quit; // Variable agregada

    int centerX;
    int centerY;
    const int MOVEMENT_SPEED = 5;
};

#endif // SDL_MANAGER_H

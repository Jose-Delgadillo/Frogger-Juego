#include "SDLManager.h"
#define SDL_MAIN_HANDLED

int main(int argc, char* args[])
{
    SDLManager sdlManager;

    if (!sdlManager.init())
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    if (!sdlManager.loadMedia())
    {
        printf("Failed to load media!\n");
        return -1;
    }

    while (!sdlManager.getQuitStatus())
    {
        sdlManager.handleEvents();
        sdlManager.render();
    }

    return 0;
}

SDLManager::SDLManager() : gWindow(nullptr), gScreenSurface(nullptr), gCurrentSurface(nullptr), centerX(0), centerY(0) {}

SDLManager::~SDLManager()
{
    close();
    quit = false; // Inicializar quit a false
}

bool SDLManager::init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("DOOM PITERO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool SDLManager::loadMedia()
{
    bool success = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/images/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/images/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/images/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/images/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/images/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]; // Establecer la superficie actual

    return success;
}

void SDLManager::close()
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface *SDLManager::loadSurface(std::string path)
{
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
    }

    return loadedSurface;
}

void SDLManager::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            // Salir si se solicita cerrar la ventana
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            // Seleccionar superficies basadas en la tecla presionada
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                centerY -= MOVEMENT_SPEED;
                break;

            case SDLK_DOWN:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                centerY += MOVEMENT_SPEED;
                break;

            case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                centerX -= MOVEMENT_SPEED;
                break;

            case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                centerX += MOVEMENT_SPEED;
                break;

            default:
                break;
            }
        }
    }
}


void SDLManager::render()
{
    // Renderizar la imagen en las nuevas coordenadas del centro de la pantalla
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 187, 79, 55));
    SDL_Rect destinationRect = {centerX, centerY, 0, 0};
    SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &destinationRect);
    SDL_UpdateWindowSurface(gWindow);
}

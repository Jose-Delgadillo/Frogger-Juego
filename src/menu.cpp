#include "C:/Users/JOSÉ DELGADILLO/Desktop/Frogger/Frogger-Juego/include/menu.hpp"
#include <stdio.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

// Instancia de la clase Menu
Menu menu;

// Luego, en tu bucle principal o donde sea necesario:
menu.handleEvents(e);

int showMenu(SDL_Surface* gScreenSurface, MenuItem menuItems[], int itemCount)
{
    int choice = 0;
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        // Maneja eventos
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    choice = (choice - 1 + itemCount) % itemCount;
                    break;
                case SDLK_DOWN:
                    choice = (choice + 1) % itemCount;
                    break;
                case SDLK_RETURN:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

        // Renderiza el menú
        SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
        SDL_BlitSurface(menuItems[choice].surface, NULL, gScreenSurface, NULL);

        // Actualiza la ventana
        SDL_UpdateWindowSurface(gWindow);
    }

    return choice;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/images/menu/jugar.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    // Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/images/menu/no_jugar.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    return success;
}

void close()
{
    // Deallocate surfaces
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    // Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
}

void Menu::handleEvents(SDL_Event& e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_ = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                // Cambia a la imagen "up"
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                break;
            case SDLK_DOWN:
                // Cambia a la imagen "down"
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                break;
            case SDLK_SPACE:
                // Verifica la imagen actual y decide qué hacer
                if (gCurrentSurface == gKeyPressSurfaces[KEY_PRESS_SURFACE_UP])
                {
                    // Ingresa al bucle principal o realiza la acción deseada
                    quit_ = true;  // En este ejemplo, salir del bucle principal
                }
                else if (gCurrentSurface == gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN])
                {
                    // Cierra el programa o realiza la acción deseada
                    quit_ = true;  // En este ejemplo, salir del bucle principal y cerrar el programa
                }
                break;
            default:
                break;
            }
        }
    }
}

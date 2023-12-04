#include <SDL.h>
#include <stdio.h>

class SDLApp {
public:
    SDLApp();
    ~SDLApp();

    bool init();
    bool loadMedia();
    void close();
    void run();

private:
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    SDL_Surface* gHelloWorld;

    bool running;

    void handleEvents();
    void render();
};

SDLApp::SDLApp() : gWindow(nullptr), gScreenSurface(nullptr), gHelloWorld(nullptr), running(false) {}

SDLApp::~SDLApp() {
    close();
}

bool SDLApp::init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("DOOM PITERO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool SDLApp::loadMedia() {
    // Loading success flag
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("assets/images/mapa.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "assets/images/mapa.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void SDLApp::close() {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void SDLApp::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}

void SDLApp::render() {
    // Apply the image
    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

    // Update the surface
    SDL_UpdateWindowSurface(gWindow);
}

void SDLApp::run() {
    running = true;

    // Main loop
    while (running) {
        handleEvents();
        render();
    }
}

int sdl_main(int argc, char* args[]) {
    SDLApp app;

    // Start up SDL and create window
    if (!app.init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!app.loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Run the application
            app.run();
        }
    }

    return 0;
}

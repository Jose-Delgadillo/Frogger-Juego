#include <SDL.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <SDL_timer.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int TILE_SIZE = 64;
const int BULLET_SPEED = 8;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_SHOOT_UP,
    KEY_PRESS_SURFACE_SHOOT_DOWN,
    KEY_PRESS_SURFACE_SHOOT_LEFT,
    KEY_PRESS_SURFACE_SHOOT_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

struct Player
{
    int centerX;
    int centerY;
    KeyPressSurfaces currentDirection;
    SDL_Surface* surfaces[KEY_PRESS_SURFACE_TOTAL][2];
};

struct Bullet
{
    int x;
    int y;
    KeyPressSurfaces direction;
    SDL_Surface* surface;
};

// Declarar las texturas globales
SDL_Surface* tile1 = nullptr;
SDL_Surface* tile2 = nullptr;
SDL_Surface* tile3 = nullptr;

bool init();
bool loadMedia(Player& player);
void close(Player& player);
SDL_Surface* loadSurface(std::string path);
void renderMap(int map[]);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        Player player;
        player.centerX = SCREEN_WIDTH / 2;
        player.centerY = SCREEN_HEIGHT / 2;
        player.currentDirection = KEY_PRESS_SURFACE_UP;

        if (!loadMedia(player))
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool isShooting = false;
            bool quit = false;
            SDL_Event e;

            Uint32 shootAnimationStartTime = 0;
            const Uint32 SHOOT_ANIMATION_DURATION = 500;

            Uint32 lastUpdateTime = SDL_GetTicks();

            // Vector para almacenar las balas
            std::vector<Bullet> bullets;

            // Mapa de tiles
            int mapa[100] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 2, 3, 3, 3, 3,
    3, 3, 1, 3, 3, 3, 3, 1, 3, 3,
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 1, 3, 3, 3, 2, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 1, 3, 3,
    3, 3, 1, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

            while (!quit)
            {
                Uint32 currentTime = SDL_GetTicks();
                Uint32 deltaTime = currentTime - lastUpdateTime;

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
                            player.currentDirection = KEY_PRESS_SURFACE_UP;
                            break;

                        case SDLK_DOWN:
                            player.currentDirection = KEY_PRESS_SURFACE_DOWN;
                            break;

                        case SDLK_LEFT:
                            player.currentDirection = KEY_PRESS_SURFACE_LEFT;
                            break;

                        case SDLK_RIGHT:
                            player.currentDirection = KEY_PRESS_SURFACE_RIGHT;
                            break;
                        case SDLK_SPACE:
                            if (!isShooting)
                            {
                                isShooting = true;
                                shootAnimationStartTime = currentTime;

                                // Crear una nueva bala y agregarla al vector
                                Bullet bullet;
                                bullet.x = player.centerX;
                                bullet.y = player.centerY;
                                bullet.direction = player.currentDirection;
                                bullet.surface = player.surfaces[player.currentDirection][1];
                                bullets.push_back(bullet);
                            }
                            break;

                        default:
                            break;
                        }
                    }
                    else if (e.type == SDL_KEYUP)
                    {
                        if (e.key.keysym.sym == SDLK_SPACE)
                        {
                            isShooting = false;
                        }
                    }
                }

                const int MOVEMENT_SPEED = 5;

                switch (player.currentDirection)
                {
                case KEY_PRESS_SURFACE_UP:
                    if (player.centerY - MOVEMENT_SPEED >= 0)  // Verifica límite superior
                        player.centerY -= MOVEMENT_SPEED;
                    break;

                case KEY_PRESS_SURFACE_DOWN:
                    if (player.centerY + MOVEMENT_SPEED + TILE_SIZE <= SCREEN_HEIGHT)  // Verifica límite inferior
                        player.centerY += MOVEMENT_SPEED;
                    break;

                case KEY_PRESS_SURFACE_LEFT:
                    if (player.centerX - MOVEMENT_SPEED >= 0)  // Verifica límite izquierdo
                        player.centerX -= MOVEMENT_SPEED;
                    break;

                case KEY_PRESS_SURFACE_RIGHT:
                    if (player.centerX + MOVEMENT_SPEED + TILE_SIZE <= SCREEN_WIDTH)  // Verifica límite derecho
                        player.centerX += MOVEMENT_SPEED;
                    break;

                default:
                    break;
                }

                // Renderiza la superficie actual
                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 187, 79, 55));

                // Renderizar el mapa de tiles
                renderMap(mapa);

                // Renderizar al jugador
                SDL_Rect destinationRect = {player.centerX, player.centerY, 0, 0};
                SDL_BlitSurface(player.surfaces[player.currentDirection][0], NULL, gScreenSurface, &destinationRect);

                // Actualizar la posición de las balas
                for (auto& bullet : bullets)
                {
                    switch (bullet.direction)
                    {
                    case KEY_PRESS_SURFACE_UP:
                        bullet.y -= BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_DOWN:
                        bullet.y += BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_LEFT:
                        bullet.x -= BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_RIGHT:
                        bullet.x += BULLET_SPEED;
                        break;

                    default:
                        break;
                    }
                }

                // Renderizar las balas
                for (const auto& bullet : bullets)
                {
                    SDL_Rect bulletRect = {bullet.x, bullet.y, 0, 0};
                    SDL_BlitSurface(bullet.surface, NULL, gScreenSurface, &bulletRect);
                }

                // Actualizar la ventana
                SDL_UpdateWindowSurface(gWindow);

                // Eliminar balas que están fuera de la pantalla
                bullets.erase(
                    std::remove_if(bullets.begin(), bullets.end(),
                                   [](const Bullet& bullet) {
                                       return bullet.x < 0 || bullet.x >= SCREEN_WIDTH || bullet.y < 0 || bullet.y >= SCREEN_HEIGHT;
                                   }),
                    bullets.end());

                lastUpdateTime = currentTime;

                SDL_Delay(16);
            }
        }
    }

    Player player;
    close(player);
    return 0;
}

bool init()
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

bool loadMedia(Player& player)
{
    bool success = true;

    // Imágenes de movimiento hacia arriba
    player.surfaces[KEY_PRESS_SURFACE_UP][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerUP.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_UP][0] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_UP][1] = loadSurface("assets/images/Armas/BFG/BalaUp.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_UP][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia abajo
    player.surfaces[KEY_PRESS_SURFACE_DOWN][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerDown.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_DOWN][0] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_DOWN][1] = loadSurface("assets/images/Armas/BFG/BalaDown.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_DOWN][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia la izquierda
    player.surfaces[KEY_PRESS_SURFACE_LEFT][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerLeft.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_LEFT][0] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_LEFT][1] = loadSurface("assets/images/Armas/BFG/BalaLeft.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_LEFT][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia la derecha
    player.surfaces[KEY_PRESS_SURFACE_RIGHT][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerRight.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_RIGHT][0] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_RIGHT][1] = loadSurface("assets/images/Armas/BFG/BalaRight.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_RIGHT][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    return success;
}

void close(Player& player)
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            SDL_FreeSurface(player.surfaces[i][j]);
            player.surfaces[i][j] = NULL;
        }
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 177, 64));
    }

    return loadedSurface;
}

void renderMap(int map[])
{
    // Renderizar el mapa de tiles en la pantalla
    for (int i = 0; i < 100; ++i)
    {
        int tileX = (i % 10) * TILE_SIZE;
        int tileY = (i / 10) * TILE_SIZE;

        SDL_Rect tileRect = {tileX, tileY, TILE_SIZE, TILE_SIZE};

        switch (map[i])
        {
        case 1:
            // Renderizar tile 1 (puedes cargar la imagen correspondiente)
            tile1 = loadSurface("assets/images/Tiles/1.png");
            SDL_BlitSurface(tile1, NULL, gScreenSurface, &tileRect);
            break;

        case 2:
            // Renderizar tile 2 (puedes cargar la imagen correspondiente)
            tile2 = loadSurface("assets/images/Tiles/2.png");
            SDL_BlitSurface(tile2, NULL, gScreenSurface, &tileRect);
            break;

        case 3:
            // Renderizar tile 3 (puedes cargar la imagen correspondiente)
            tile3 = loadSurface("assets/images/Tiles/3.png");
            SDL_BlitSurface(tile3, NULL, gScreenSurface, &tileRect);
            break;

        // Agrega más casos según los tipos de tiles que tengas
        // ...

        default:
            // Renderizar tile por defecto (puedes cargar la imagen correspondiente)
            SDL_BlitSurface(tile3, NULL, gScreenSurface, &tileRect);
            break;
        }
    }
}


#include "mapa.h"

int main(int argc, char* args[]) {
    SDLApp sdlApp;

    // Inicializa SDL y crea la ventana
    if (!sdlApp.init()) {
        printf("¡Error al inicializar!\n");
    } else {
        // Carga los recursos multimedia
        if (!sdlApp.loadMedia()) {
            printf("¡Error al cargar los medios!\n");
        } else {
            // Ejecuta la aplicación
            sdlApp.run();
        }
    }

    return 0;
}

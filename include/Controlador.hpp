#pragma once
#include <Actualizable.hpp>
#include <Dibujo.hpp>
#include <curses.h>

class Controlador : public Actualizable
{
private:
    Dibujo *d1;
    Dibujo *d2;

public:
     Controlador(Dibujo* dibujo1, Dibujo* dibujo2) : d1(dibujo1), d2(dibujo2) {}
    ~Controlador();
    
    void Actualizar()
    {
         if(getch() == 'd'){
             d1->AvanzarX(1);
         }
         if(getch() == 'a'){
             d1->RetrocederX(1);
         }
         if(getch() == 'w'){
             d1->SaltarY(1);
         }
         if(getch() == 's'){
             d1->BajarY(1);
         }
         if(getch() == KEY_RIGHT){
             d2->AvanzarX(1);
         }
         if(getch() == KEY_LEFT){
             d2->RetrocederX(1);
         }
         if(getch() == KEY_UP){
             d2->SaltarY(1);
         }
         if(getch() == KEY_DOWN){
             d2->BajarY(1);
         }
    }
};

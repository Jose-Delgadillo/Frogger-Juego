#pragma once
#include <Dibujo.hpp>
#include <Actualizable.hpp>

class Frog : public Dibujo, public Actualizable
{
private:
    /* data */
public:
    Frog(/* args */) : Dibujo("frog")
        {

        }
    ~Frog
() {}
    void Actualizar() {
        
    }
};

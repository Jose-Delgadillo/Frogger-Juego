#pragma once
#include <Dibujo.hpp>
#include <curses.h>

class Marco : public Dibujo
{
private:
    /* data */
public:
    Marco(/* args */) {}
    ~Marco() {}
    void Dibujar()
    {
        box(stdscr,'#','#');
    }
};
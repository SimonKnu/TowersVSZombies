#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "menu.h"

#include "SFML/Graphics.hpp"

#include <vector>

class MenuWindow
{
    private:
        std::vector<Menu*>  menus;

    public:
        MenuWindow();
        ~MenuWindow();

        void dessiner(sf::RenderWindow *window);
};

#endif // MENUWINDOW_H

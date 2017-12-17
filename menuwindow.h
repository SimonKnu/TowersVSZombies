#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "SFML/Graphics.hpp"
#include "containeur.h"
#include "menu.h"

class Containeur;

class MenuWindow : public Containeur
{
    private:
        std::vector<Menu*>  menus;
        int compteur=0;

    public:
        MenuWindow(sf::RenderWindow * containeur);
        MenuWindow(const MenuWindow &window);
        ~MenuWindow();
        MenuWindow& operator=(const MenuWindow& window);

        void drawElements();
        int chosenMenu(sf::Event e);
};

#endif // MENUWINDOW_H

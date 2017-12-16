#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include "SFML/Graphics.hpp"
#include "containeur.h"
#include "vector"
#include "menu.h"

class EndWindow : public Containeur
{
    private :
        std::vector<Menu *> menus;
        int compteur=0;

    public :
        EndWindow(sf::RenderWindow * containeur);
        ~EndWindow();

        void drawElements();
        int chosenMenu(sf::Event e);
};

#endif // ENDWINDOW_H

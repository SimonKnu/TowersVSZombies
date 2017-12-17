#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <SFML/Graphics.hpp>
#include "containeur.h"
#include "menu.h"
#include <vector>

class WaitWindow : public Containeur
{
    private:
        std::vector<Menu *> menus;
        int compteur=0;

    public:
        WaitWindow(sf::RenderWindow *containeur);
        WaitWindow(const WaitWindow &window);
        ~WaitWindow();
        WaitWindow& operator=(const WaitWindow& window);

        void drawElements();
        int chosenMenu(sf::Event e);
};

#endif // WAITWINDOW_H

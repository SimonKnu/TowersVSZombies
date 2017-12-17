#ifndef TUTOWINDOW_H
#define TUTOWINDOW_H

#include "SFML/Graphics.hpp"
#include "containeur.h"
#include "menu.h"
#include <vector>

class TutoWindow : public Containeur
{
    private:
        std::vector<Menu *> menus;

    public:
        TutoWindow(sf::RenderWindow *containeur);
        TutoWindow(const TutoWindow &window);
        ~TutoWindow();
        TutoWindow& operator=(const TutoWindow& window);

        void drawElements();
        int chosenMenu(sf::Event e);
};

#endif // TUTOWINDOW_H

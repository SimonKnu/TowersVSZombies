#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <SFML/Graphics.hpp>
#include "containeur.h"
#include <vector>
#include "menu.h"

class AboutWindow : public Containeur
{
    private:
        std::vector<Menu *> menus;

    public:
        AboutWindow(sf::RenderWindow *containeur);
        AboutWindow(const AboutWindow &window);
        ~AboutWindow();
        AboutWindow& operator=(const AboutWindow& window);

        void drawElements();
        int chosenMenu(sf::Event e);
};

#endif // ABOUTWINDOW_H

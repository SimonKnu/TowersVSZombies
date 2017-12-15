#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu
{
    private:
        sf::Text title;
        sf::Font font;

    public:
        Menu(std::string text, int posX, int posY);

        sf::Text getText() const;
        void changerColor(const sf::Color col);
        void changerText(const std::string val);

};

#endif // MENU_H

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <SFML/Graphics.hpp>

class AboutWindow
{
    public:
    AboutWindow();
    ~AboutWindow();

    void dessiner(sf::RenderWindow *window);
};

#endif // ABOUTWINDOW_H

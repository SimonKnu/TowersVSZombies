#ifndef CONTAINEUR_H
#define CONTAINEUR_H

#include "SFML/Graphics.hpp"

class Containeur
{
    private:
        sf::RenderWindow * containeur;

    public:
        Containeur(sf::RenderWindow *containeur);
        ~Containeur();

        virtual void drawElements()=0;
        virtual int chosenMenu(sf::Event e)=0;

        sf::RenderWindow* getWindow() const;
        void setWindow(sf::RenderWindow * containeur);
};

#endif // CONTAINEUR_H

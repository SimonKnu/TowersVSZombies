#ifndef CONTAINEUR_H
#define CONTAINEUR_H

#include "SFML/Graphics.hpp"

class Containeur
{
    private:
        sf::RenderWindow * containeur;

    public:
        Containeur(sf::RenderWindow *containeur);
        Containeur(const Containeur &window);
        ~Containeur();
        Containeur& operator=(const Containeur& window);

        //Deux méthodes qui seront définies dans chacune des classes
        //qui hériteront de la classe Containeur
        virtual void drawElements()=0;
        virtual int chosenMenu(sf::Event e)=0;

        //Permet de récupérer la fenêtre
        sf::RenderWindow* getWindow() const;
};

#endif // CONTAINEUR_H

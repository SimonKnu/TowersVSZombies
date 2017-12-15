#include <SFML/Graphics.hpp>
#include "menuwindow.h"
#include "endwindow.h"
#include "mainwindow.h"

#include <vector>

int main(){
    /*
    sf::RenderWindow* fenetre = new sf::RenderWindow(sf::VideoMode(800,600),"TowersVSZombies");

    int compteurWindow = 0;

    std::vector<Window *> containeur;
    containeur.push_back(new MenuWindow(fenetre));
    containeur.push_back(new MainWindow(fenetre));
    containeur.push_back(new EndWindow(fenetre));*/

    new MainWindow();
    return 0;
}




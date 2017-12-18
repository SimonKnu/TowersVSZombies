#include "aboutwindow.h"

//********************************************************************************//

AboutWindow::AboutWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Game realized by Cannuyer, Lepape & Papleux",1080/2, 720/6));
    menus.push_back(new Menu("students from HELHa of Mons",1080/2, 720/3));
    menus.push_back(new Menu("as part of the course of Mr. V. Altares.",1080/2, 720/2));

    menus.push_back(new Menu("Back",1080/2, 720/1.2));
    menus.at(3)->changerColor(sf::Color::White);
}

AboutWindow::AboutWindow(const AboutWindow &window):Containeur(window){
    for(int i=0; i<menus.size();i++){
        menus.push_back(new Menu(*window.menus.at(i)));
    }
}

AboutWindow::~AboutWindow(){
    for(int i=0;i<menus.size();i++){
        delete menus.at(i);
        menus.at(i)=0;
    }
    menus.clear();
}


AboutWindow& AboutWindow::operator=(const AboutWindow& window){
    if(this!=&window){
        Containeur::operator=(window);
        for(int i=0; i<menus.size();i++){
            menus.push_back(new Menu(*window.menus.at(i)));
        }
    }
    return *this;
}

//********************************************************************************//

void AboutWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());      //On traite et affiche les éléments de la fenêtre
    }
}

int AboutWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Escape){
        return 0;               //Retour au menu principal
    }
    return 2;                   //On reste sur cette page tant qu'il ne se passe rien
}

#include "aboutwindow.h"

AboutWindow::AboutWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Game realized by Cannuyer, Lepape & Papleux",sf::VideoMode::getDesktopMode().width/4, sf::VideoMode::getDesktopMode().height/12));
    menus.push_back(new Menu("students from HELHa of Mons",sf::VideoMode::getDesktopMode().width/4, sf::VideoMode::getDesktopMode().height/6));
    menus.push_back(new Menu("as part of the course of Mr. V. Altares.",sf::VideoMode::getDesktopMode().width/4, sf::VideoMode::getDesktopMode().height/4));

    menus.push_back(new Menu("Back",sf::VideoMode::getDesktopMode().width/4, sf::VideoMode::getDesktopMode().height/2.4));
    menus.at(3)->changerColor(sf::Color::White);
}

AboutWindow::~AboutWindow(){
}

void AboutWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int AboutWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Escape){
        return 0;
    }
    return 2;
}

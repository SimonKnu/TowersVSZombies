#include "menu.h"
#include <iostream>

Menu::Menu(){

}

Menu::Menu(std::string text, int posX, int posY){
    if(!font.loadFromFile("bloodgut.ttf")){
        std::cout<< "Erreur de chargement de la police !" << std::endl;
    }
    title.setFillColor(sf::Color::Red);
    title.setFont(font);

    title.setString(text);
    title.setPosition(sf::Vector2f(posX, posY));
    title.setOrigin(title.getLocalBounds().width/2.0f,title.getLocalBounds().height/2.0f);
}

sf::Text Menu::getText() const{
    return this->title;
}

void Menu::changerColor(const sf::Color col){
    title.setFillColor(col);
}

void Menu::changerText(const std::string val){
    title.setString(val);
    title.setOrigin(title.getLocalBounds().width/2.0f, title.getLocalBounds().height/2.0f);
}

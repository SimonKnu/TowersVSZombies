#include "containeur.h"

Containeur::Containeur(sf::RenderWindow * containeur){
    this->containeur = containeur;
}

Containeur::~Containeur(){
    delete containeur;
    containeur=0;
}



sf::RenderWindow* Containeur::getWindow() const{
    return containeur;
}

void Containeur::setWindow(sf::RenderWindow *containeur){
    this->containeur = containeur;
}

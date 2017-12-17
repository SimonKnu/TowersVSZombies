#include "containeur.h"

//********************************************************************************//

Containeur::Containeur(sf::RenderWindow * containeur){
    this->containeur = containeur;
}

Containeur::Containeur(const Containeur &window){
    this->containeur = window.containeur;
}

Containeur::~Containeur(){
    delete containeur;
    containeur=0;
}

Containeur& Containeur::operator=(const Containeur& window){
    if(this!=&window){
        this->containeur = window.containeur;
    }
    return *this;
}

//********************************************************************************//

sf::RenderWindow* Containeur::getWindow() const{
    return containeur;
}

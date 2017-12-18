#include "tower.h"
#include <iostream>
#include <sstream>

using std::stringstream;

//********************************************************************************//

Tower::Tower(int sizeX, int sizeY, int posX, int posY)
{
    animation=1;
    if(!texture.loadFromFile("turret1.png")){
        std::cout<< "erreur de chargement du sprite!" << std::endl;
    }
    else{
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));
        sprite.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    }

}

Tower::Tower(const Tower &t){
    this->sprite=t.sprite;
    this->animation=t.animation;
}

Tower::~Tower(){

}

Tower& Tower::operator=(const Tower &t){
    if(&t != this){
        this->sprite=t.sprite;
        this->animation=t.animation;
    }
    return *this;
}

//********************************************************************************//

sf::Sprite Tower::getSprite()
{
    return sprite;
}

sf::Vector2f Tower::getPosition()
{
    return sprite.getPosition();
}

void Tower::rotate(float r)
{
    sprite.setRotation(r);
}

//permet d'animer les drones
void Tower::changeAnimation(){
    animation++;
    if(animation>6){
        animation=1;
    }
    stringstream ss;
    ss<<"turret"<<animation<<".png";
    if(!texture.loadFromFile(ss.str())){
        std::cout<< "erreur de chargement du sprite!" << std::endl;
    }else{
        sprite.setTexture(texture);
    }
}

#include "enemy.h"
#include <iostream>

        //CONSTRUCTOR//
Enemy::Enemy()
{

}

Enemy::Enemy(int sizeX, int sizeY, int posX, int posY, float speed, float health){
//    rect = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
//    rect.setPosition(sf::Vector2f(posX,posY));
//    rect.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
//    rect.setFillColor(sf::Color(70,125,20,255));

    if(!texture.loadFromFile("zombie.png")){
        std::cout<< "erreur de chargement du sprite du zombie!" << std::endl;
    }else{
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));
        sprite.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    }

    this->speed=speed;
    this->health=health;
}

Enemy::Enemy(const Enemy &p)
{
    this->speed = p.speed;
    this->sprite = p.sprite;
    this->health = p.health;
}
//--------------------------------//

        //DESTRUCTOR//
Enemy::~Enemy()
{

}
//-------------------------//

        //OPERATOR//
Enemy& Enemy::operator=(const Enemy &p)
{
    if(&p != this){
        this->speed = p.speed;
        this->sprite = p.sprite;
        this->health=p.health;
    }
    return *this;
}
//------------------------//

        //OTHERS//
void Enemy::move(float x, float y)
{
    sprite.move(x, y);
}

void Enemy::rotate(float r)
{
    sprite.setRotation(r);
}

float Enemy::getSpeed()
{
    return speed;
}

void Enemy::setPosition(int x, int y){
    sprite.setPosition(sf::Vector2f(x,y));
}

sf::Vector2f Enemy::getOrigin()
{
    return sprite.getOrigin();
}

sf::Sprite Enemy::getRect()
{
    return sprite;
}

sf::Vector2f Enemy::getPosition()
{
    return sprite.getPosition();
}

void Enemy::setHealth(const float damage){
    this->health-=damage;
}

float Enemy::getHealth() const{
    return this->health;
}

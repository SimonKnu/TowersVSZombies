#include "enemy.h"

//CONSTRUCTOR//
Enemy::Enemy()
{

}

Enemy::Enemy(int sizeX, int sizeY, int posX, int posY, float speed, float health){
    rect = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(sf::Vector2f(posX,posY));
    rect.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    rect.setFillColor(sf::Color(70,125,20,255));
    this->speed=speed;
    this->health=health;
}

Enemy::Enemy(const Enemy &p)
{
    this->sizeX = p.sizeX;
    this->sizeY = p.sizeY;
    this->speed = p.speed;
    this->rect = p.rect;
    this->health=p.health;
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
        this->sizeX = p.sizeX;
        this->sizeY = p.sizeY;
        this->speed = p.speed;
        this->rect = p.rect;
        this->health=p.health;
    }
    return *this;
}
//------------------------//

//OTHERS//
void Enemy::move(float x, float y)
{
    rect.move(x, y);
}

void Enemy::rotate(float r)
{
    rect.setRotation(r);
}

float Enemy::getSpeed()
{
    return speed;
}

sf::Vector2f Enemy::getOrigin()
{
    return rect.getOrigin();
}

sf::RectangleShape Enemy::getRect()
{
    return rect;
}

sf::Vector2f Enemy::getPosition()
{
    return rect.getPosition();
}

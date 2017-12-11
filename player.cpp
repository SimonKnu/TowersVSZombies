//INCLUDES//
#include "player.h"
//-----------------------------//

//CONSTRUCTOR//
Player::Player()
{

}

Player::Player(int sizeX, int sizeY, int posX, int posY, float speed){
    rect = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(sf::Vector2f(posX,posY));
    rect.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    rect.setFillColor(sf::Color(33,42,231,255));
    this->speed=speed;
}

Player::Player(const Player &p)
{
    this->sizeX = p.sizeX;
    this->sizeY = p.sizeY;
    this->speed = p.speed;
    this->rect = p.rect;
}
//--------------------------------//

//DESTRUCTOR//
Player::~Player()
{

}
//-------------------------//

//OPERATOR//
Player &Player::operator=(const Player &p)
{
    this->sizeX = p.sizeX;
    this->sizeY = p.sizeY;
    this->speed = p.speed;
    this->rect = p.rect;
}
//------------------------//

//OTHERS//
void Player::move(float x, float y)
{
    rect.move(x, y);
}

void Player::rotate(float r)
{
    rect.setRotation(r);
}

float Player::getSpeed()
{
    return speed;
}

sf::Vector2f Player::getOrigin()
{
    return rect.getOrigin();
}

sf::RectangleShape Player::getRect()
{
    return rect;
}

sf::Vector2f Player::getPosition()
{
    return rect.getPosition();
}





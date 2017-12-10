#include "player.h"

Player::Player(int tailleX, int tailleY, int posX, int posY, float speed){
    rect = sf::RectangleShape(sf::Vector2f(tailleX, tailleY));
    rect.setPosition(sf::Vector2f(posX,posY));
    rect.setFillColor(sf::Color(33,42,231,255));
    this->speed=speed;
}

Player::move(int x, int y)
{
    rect.move(x, y);
}

float Player::getSpeed()
{
    return speed;
}

sf::RectangleShape Player::getRect()
{
    return rect;
}

Player &Player::operator=(const Player &p)
{
    this->tailleX = p.tailleX;
    this->tailleY = p.tailleY;
    this->speed = p.speed;
    this->rect = p.rect;
}

Player::Player(Player &p)
{
    this->tailleX = p.tailleX;
    this->tailleY = p.tailleY;
    this->speed = p.speed;
    this->rect = p.rect;
}



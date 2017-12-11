#include "bullet.h"
#include <SFML/Graphics.hpp>

Bullet::Bullet(float radius): currVelocity(0.f, 0.f), maxSpeed(1.5)
{
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Red);
}

sf::CircleShape Bullet::getShape()
{
    return shape;
}

sf::Vector2f Bullet::getCurrVelocity()
{
    return currVelocity;
}

float Bullet::getMaxSpeed()
{
    return maxSpeed;
}

void Bullet::setCurrVelocity(sf::Vector2f newVelocity)
{
    this->currVelocity = newVelocity;
}

void Bullet::setShapePosition(sf::Vector2f vect)
{
    shape.setPosition(vect);
}

void Bullet::moveShape()
{
    shape.move(this->currVelocity);
}


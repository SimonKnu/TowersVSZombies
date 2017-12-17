#include "bullet.h"

//********************************************************************************//

Bullet::Bullet(float radius): currVelocity(0.f, 0.f), maxSpeed(1){
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Red);
}

Bullet::Bullet(const Bullet &b){
    this->currVelocity = b.currVelocity;
    this->maxSpeed = b.maxSpeed;
    this->shape = b.shape;
}

Bullet::~Bullet(){

}

Bullet& Bullet::operator=(const Bullet &b){
    if(&b != this){
        this->currVelocity = b.currVelocity;
        this->maxSpeed = b.maxSpeed;
        this->shape = b.shape;
    }
    return *this;
}

//********************************************************************************//

bool Bullet::checkCollisionBorder(){
    if (this->getShape().getPosition().x < 0 ||this->getShape().getPosition().x >1080
            ||this->getShape().getPosition().y < 0 || this->getShape().getPosition().y > 720)
    {
        return true;
    }else{
        return false;
    }
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


        //INCLUDES//
#include "player.h"

//-----------------------------//
Player* Player::instance = 0;

        //CONSTRUCTOR//

Player::Player(int sizeX, int sizeY, int posX, int posY, float speed, float health, int money){
    rect = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(sf::Vector2f(posX,posY));
    rect.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    rect.setFillColor(sf::Color(33,42,231,255));

    this->money = money;
    this->health = health;
    this->speed=speed;
}

Player::Player(const Player &p)
{
    this->money = p.money;
    this->health = p.health;
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
Player& Player::operator=(const Player &p)
{
    if(&p != this){
        this->money = p.money;
        this->health = p.health;
        this->speed = p.speed;
        this->rect = p.rect;
    }
    return *this;
}
//------------------------//

        //OTHERS//
Player* Player::getInstance(){
    if(instance==0){
        instance = new Player(32,32,16,16,0.1,100,0);
    }
    return instance;
}



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


sf::Vector2f Player::getPosition()
{
    return rect.getPosition();
}
void Player::setPosition(int x, int y){
    rect.setPosition(sf::Vector2f(x,y));
}

sf::Vector2f Player::getOrigin()
{
    return rect.getOrigin();
}

sf::RectangleShape Player::getRect()
{
    return rect;
}






#include "player.h"
#include <iostream>

Player* Player::instance = 0;



//-----------------------------------------------------------------------//
                        //FORME CANONIQUE//

Player::Player(int sizeX, int sizeY, int posX, int posY, float speed, float health, int money){
    if(!texture.loadFromFile("player_static.png")){
        std::cout<< "erreur de chargement du sprite!" << std::endl;
    }
    else{
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));
        sprite.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    }

    this->money = money;
    this->health = health;
    this->speed=speed;
}

Player::Player(const Player &p){
    this->money = p.money;
    this->health = p.health;
    this->speed = p.speed;
    this->sprite = p.sprite;
}

Player::~Player(){

}

Player& Player::operator=(const Player &p){
    if(&p != this){
        this->money = p.money;
        this->health = p.health;
        this->speed = p.speed;
        this->sprite = p.sprite;
    }
    return *this;
}

Player* Player::getInstance(){
    if(instance==0){
        instance = new Player(64,64,50,50,0.1,100,0);
    }
    return instance;
}



//-----------------------------------------------------------------------//



void Player::move(float x, float y)
{
    sprite.move(x, y);
}

void Player::rotate(float r)
{
    sprite.setRotation(r);
}

float Player::getSpeed()
{
    return speed;
}

int Player::getMoney(){
    return money;
}

float Player::getHealth(){
    return health;
}

void Player::setHealth(float health){
    this->health = health;
}

void Player::setMoney(int money){
    this->money = money;
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}

void Player::setTexture(int i)
{
    switch(i){
        case 0: texture.loadFromFile("player_static.png");break;
        case 1: texture.loadFromFile("player.png");break;
        case 2: texture.loadFromFile("player_bis.png");break;
    }
    sprite.setTexture(texture);
}
void Player::setPosition(int x, int y){
    sprite.setPosition(sf::Vector2f(x,y));
}

sf::Vector2f Player::getOrigin()
{
    return sprite.getOrigin();
}

sf::Sprite Player::getRect()
{
    return sprite;
}






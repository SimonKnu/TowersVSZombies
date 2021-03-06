#include "enemy.h"
#include <iostream>

//********************************************************************************//

Enemy::Enemy(int sizeX, int sizeY, int posX, int posY, float speed, float health, float damage){
    if(!texture.loadFromFile("zombie.png")){
        std::cout<< "Erreur lors du chargement du sprite du zombie !" << std::endl;
    }
    else{
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));
        sprite.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
    }

    this->speed=speed;
    this->health=health;
    this->damage=damage;
    this->animated=false;
}

Enemy::Enemy(const Enemy &p){
    this->speed = p.speed;
    this->sprite = p.sprite;
    this->health = p.health;
    this->damage = p.damage;
}

Enemy::~Enemy(){

}

Enemy& Enemy::operator=(const Enemy &p){
    if(&p != this){
        this->speed = p.speed;
        this->sprite = p.sprite;
        this->health=p.health;
        this->damage = p.damage;
    }
    return *this;
}

//********************************************************************************//

void Enemy::goBack(){
    this->setPosition(previousPosition.x, previousPosition.y);
}

void Enemy::setPreviousPosition(){
    previousPosition.x = this->getPosition().x;
    previousPosition.y = this->getPosition().y;
}

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

float Enemy::getDamage(){
    return damage;
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

//permet d'animer les zombies
void Enemy::changeAnimation()
{
    if(animated){
        if(!texture.loadFromFile("zombie.png")){
            std::cout<< "erreur de chargement du sprite!" << std::endl;
        }else{
            sprite.setTexture(texture);
        }
        animated=false;
    }else{
        if(!texture.loadFromFile("zombie_bis.png")){
            std::cout<< "erreur de chargement du sprite!" << std::endl;
        }else{
            sprite.setTexture(texture);
        }
        animated=true;
    }
}



#ifndef ENEMY_H
#define ENEMY_H

#include <SFMl/Graphics.hpp>

class Enemy {

    private:
        float speed;
        float health;
        float damage;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f previousPosition;

    public:
        Enemy(int sizeX=64, int sizeY=64, int posX=0, int posY=0, float speed=0.20, float health=100, float damage=25);
        Enemy(const Enemy &p);
        ~Enemy();
        Enemy& operator=(const Enemy& p);

        void move(float x, float y);
        void rotate(float r);
        void setPosition (int x, int y);
        float getSpeed();
        float getDamage();
        sf::Vector2f getOrigin();
        sf::Sprite getRect();
        sf::Vector2f getPosition();
        void setHealth(const float damage);
        float getHealth() const;

        void setPreviousPosition();
        void goBack();

};

#endif // ENEMY_H

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

    public:
        Enemy();
        Enemy(int sizeX, int sizeY, int posX, int posY, float speed, float health, float damage);
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

};

#endif // ENEMY_H

#ifndef ENEMY_H
#define ENEMY_H
#include <SFMl/Graphics.hpp>

class Enemy {

    private:
        int sizeX, sizeY;
        float speed;
        float health;
        sf::RectangleShape rect;

    public:
        Enemy();
        Enemy(int sizeX, int sizeY, int posX, int posY, float speed, float health);
        Enemy(const Enemy &p);

        ~Enemy();

        Enemy &operator=(const Enemy& p);

        void move(float x, float y);
        void rotate(float r);

        float getSpeed();
        sf::Vector2f getOrigin();
        sf::RectangleShape getRect();
        sf::Vector2f getPosition();
};

#endif // ENEMY_H

#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {

    public:
        Bullet(float radius = 5.f);
        Bullet(const Bullet &b);
        ~Bullet();
        Bullet& operator=(const Bullet& b);

        sf::CircleShape getShape();
        sf::Vector2f getCurrVelocity();
        float getMaxSpeed();
        void setCurrVelocity(sf::Vector2f newVelocity);
        void setShapePosition(sf::Vector2f vect);
        void moveShape();
        bool checkCollisionBorder();

    private:
        sf::CircleShape shape;
        sf::Vector2f currVelocity;
        float maxSpeed;


};

#endif // BULLET_H


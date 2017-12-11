#ifndef PLAYER_H
#define PLAYER_H
#include <SFMl/Graphics.hpp>


class Player{
private:
    int sizeX, sizeY;
    float speed;
    sf::RectangleShape rect;
public:
    Player();
    Player(int sizeX, int sizeY, int posX, int posY, float speed);
    Player(const Player &p);

    ~Player();

    Player &operator=(const Player& p);

    void move(float x, float y);
    void rotate(float r);

    float getSpeed();
    sf::Vector2f getOrigin();
    sf::RectangleShape getRect();
    sf::Vector2f getPosition();
};

#endif // PLAYER_H

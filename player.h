#ifndef PLAYER_H
#define PLAYER_H
#include <SFMl/Graphics.hpp>


class Player{
private:
    int tailleX, tailleY;
    float speed;
    sf::RectangleShape rect;
public:
    Player(int tailleX, int tailleY, int posX, int posY, float speed);
    move(int x, int y);
    float getSpeed();
    sf::RectangleShape getRect();
    Player &operator=(const Player& p);
    Player(Player &p);
};

#endif // PLAYER_H

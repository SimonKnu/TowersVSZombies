#ifndef TOWER_H
#define TOWER_H
#include <SFML/Graphics.hpp>


class Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int animation;
public:
    Tower(int sizeX=64, int sizeY=64, int posX=400, int posY=400);
    Tower(const Tower &p);
    ~Tower();
    Tower& operator=(const Tower& p);

    sf::Sprite getSprite();
    sf::Vector2f getPosition();
    void rotate(float r);
    void changeAnimation();
};

#endif // TOWER_H

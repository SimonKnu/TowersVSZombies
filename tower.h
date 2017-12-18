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
    Tower();
    Tower(const Tower &p);
    ~Tower();
    Tower& operator=(const Tower& p);
    Tower(int sizeX, int sizeY, int posX, int posY);

    sf::Sprite getSprite();
    sf::Vector2f getPosition();
    void rotate(float r);
    void changeAnimation();
};

#endif // TOWER_H

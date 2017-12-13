#ifndef PLAYER_H
#define PLAYER_H
#include <SFMl/Graphics.hpp>


class Player {

    private:
        float speed;
        sf::RectangleShape rect;
        float health;
        int money;

        static Player* instance;
        Player(int sizeX, int sizeY, int posX, int posY, float speed, float health, int money);

    public:
        ~Player();
        Player& operator=(const Player& p);
        Player(const Player &p);

        static Player* getInstance();
        void move(float x, float y);
        void rotate(float r);
        void setPosition (int x, int y);


        float getSpeed();
        sf::Vector2f getOrigin();
        sf::RectangleShape getRect();
        sf::Vector2f getPosition();

};

#endif // PLAYER_H

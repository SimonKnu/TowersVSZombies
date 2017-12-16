#ifndef PLAYER_H
#define PLAYER_H

#include <SFMl/Graphics.hpp>


class Player {

    private:
        float speed;
        float health;
        int money;
        int finalWave;
        sf::Texture texture;
        sf::Sprite sprite;
        bool moving;

        static Player* instance;
        Player(int sizeX, int sizeY, int posX, int posY, float speed, float health, int money);

    public:
        ~Player();
        Player& operator=(const Player& p);
        Player(const Player &p);
        static Player* getInstance();

        void move(float x, float y);
        void rotate(float r);

        void reset();

        void setPosition (int x, int y);
        void setHealth(float health);
        void setMoney(int money);
        void setFinalWave(int wave);

        float getSpeed();
        int getMoney();
        float getHealth();
        int getFinalWave();

        bool checkCollisionBorder(int maxX, int maxY);

        sf::Vector2f getOrigin();
        sf::Sprite getRect();
        sf::Vector2f getPosition();
        void setTexture(int i);
        void setMoving(bool move);
        bool getMoving();

};

#endif // PLAYER_H

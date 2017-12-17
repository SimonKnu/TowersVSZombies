#ifndef PLAYER_H
#define PLAYER_H

#include <SFMl/Graphics.hpp>


class Player {

    private:
        float speed;
        float health;
        int money=0;
        int finalWave;

        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f previousPosition;
        bool moving;

        static Player* instance;
        Player(int sizeX=64, int sizeY=64, int posX=540, int posY=360, float speed=0.14, float health=100, int money=0);

    public:
        ~Player();
        static Player* getInstance();

        void move(float x, float y);
        void rotate(float r);

        void reset();

        void setPosition (int x, int y);
        void setHealth(float health);
        void setMoney(int money);
        void setFinalWave(int wave);
        void setPreviousPosition();
        void goBack();

        float getSpeed();
        int getMoney();
        float getHealth();
        int getFinalWave();

        bool checkCollisionBorder();

        sf::Vector2f getOrigin();
        sf::Sprite getRect();
        sf::Vector2f getPosition();
        void setTexture(int i);
        void setMoving(bool move);
        bool getMoving();

};

#endif // PLAYER_H

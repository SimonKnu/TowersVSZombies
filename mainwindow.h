#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "player.h"
#include "enemy.h"
#include "menu.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>

class MainWindow{

    public:
        MainWindow();
        ~MainWindow();

        void rotatePlayer(sf::RenderWindow* window);
        void start(sf::RenderWindow* window);
        bool chackCollision(int index);


        void dessiner(sf::RenderWindow *window);

    private:
        Player *player = Player::getInstance();
        std::vector<Enemy *> enemies;
        std::vector<Menu *> menus;
        Bullet b1;
        std::vector<Bullet *> bullets;
        int test=0;
        int test2=0;
        sf::Texture mapTexture;
            sf::Sprite map;
};

#endif // MAINWINDOW_H

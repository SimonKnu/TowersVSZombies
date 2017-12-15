#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "player.h"
#include "enemy.h"
#include "menu.h"
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
};

#endif // MAINWINDOW_H

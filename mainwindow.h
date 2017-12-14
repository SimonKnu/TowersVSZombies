#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "player.h"
#include "enemy.h"
#include "menu.h"
#include <SFML/Graphics.hpp>

class MainWindow {

    public:
        MainWindow();
        MainWindow(const MainWindow& m);
        ~MainWindow();
        MainWindow& operator=(const MainWindow& m);

        void rotatePlayer(sf::RenderWindow* window);
        void start(sf::RenderWindow* window);

    private:
        Player *player = Player::getInstance();
        std::vector<Enemy *> enemies;
        std::vector<Menu *> menus;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "enemy.h"
#include <vector>
#include <SFML/Graphics.hpp>


using std::vector;

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
        vector<Enemy *> enemies;
};

#endif // MAINWINDOW_H

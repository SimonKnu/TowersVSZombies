#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include <vector>
#include "enemy.h"
#include <SFML/Graphics.hpp>


using std::vector;

class MainWindow {

    public:
        MainWindow();
        MainWindow(const MainWindow& m);

        ~MainWindow();

        MainWindow& operator=(const MainWindow& m);

        void movePlayer(float x, float y);
        void rotatePlayer(sf::RenderWindow* window);
        void start(sf::RenderWindow* window);
        void stopWave();

    private:
        Player *player = Player::getInstance();
        vector<Enemy *> enemies;
        sf::Thread runthread;
};

#endif // MAINWINDOW_H

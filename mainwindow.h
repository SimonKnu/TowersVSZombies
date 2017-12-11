#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"

#include <SFML/Graphics.hpp>

class MainWindow{
public:
    MainWindow();
    MainWindow(Player* p);
    MainWindow(const MainWindow& m);

    ~MainWindow();

    MainWindow& operator=(const MainWindow& m);

    void movePlayer(float x, float y);
    void rotatePlayer(sf::RenderWindow* window);
    void start(sf::RenderWindow* window);

private:
    Player* player;
};

#endif // MAINWINDOW_H

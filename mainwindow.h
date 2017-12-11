#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"

#include <SFML/Graphics.hpp>

class MainWindow{
public:
    MainWindow(Player* p);

private:
    Player player;
    void movePlayer();
    void start();
};

#endif // MAINWINDOW_H

#include <QApplication>
#include "mycanvas.h"
#include <QFrame>
#include <SFML/Graphics.hpp>
#include "mainwindow.h"
#include "player.h"

int main(int argc, char *args[]){
    Player* p1 = new Player(32, 32, 10, 10, 0.1);
    MainWindow* w = new MainWindow(p1);
    return 0;
}


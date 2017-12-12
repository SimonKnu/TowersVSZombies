#include <QApplication>
#include <QFrame>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "mainwindow.h"

void launchWindow(){
    MainWindow* mainWindow = new MainWindow();
}

int main(int argc, char *args[]){
    sf::Thread threadWindow(&launchWindow);

    threadWindow.launch();
    return 0;
}




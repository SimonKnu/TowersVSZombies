#include <QApplication>
#include "mycanvas.h"
#include <QFrame>
#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include "mainwindow.h"
#include "player.h"

=======
>>>>>>> 9ca91847a9b4e5f5e826ed2b37bc8d81b741dcb7
/*
int main(int argc, char *argv[]){
    QApplication App(argc, argv);
    // Create the main frame
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(400, 400);
    MainFrame->show();
    // Create a SFML view inside the main frame
    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
    return App.exec();
}
*/

int main(int argc, char *args[]){
    Player* p1 = new Player(32, 32, 10, 10, 0.1);
    MainWindow* w = new MainWindow(p1);
    return 0;
}


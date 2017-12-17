#include <QApplication>
#include "mycanvas.h"
#include <QFrame>
#include <SFML/Graphics.hpp>
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
    sf::RenderWindow window(sf::VideoMode(800,600),"Hello");

    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(235,350));
    rect.setSize(sf::Vector2f(30,30));
    rect.setFillColor(sf::Color(33,42,231,255));

    while(window.isOpen()){
        sf::Event e;

        while(window.pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}


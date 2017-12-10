#include "mycanvas.h"
#include <iostream>
#include <string>
#include <QDir>

MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size){
}

void MyCanvas::OnInit(){
    // Load the image
    std::cout << "onInit" << std::endl;

    if (!myImage.loadFromFile("chef.png")) {
        std::cout << "Loading error"<< std::endl;
    }
    else {
        std::cout << "Image was loaded fine" << std::endl;
    }

    // Setup the sprite
    mySprite.setTexture(myImage);
    mySprite.setPosition(150, 150);
    std::cout << "setting the texture of the sprite" << std::endl;

    //mySprite.setCenter(mySprite.GetSize() / 2.f);
    myClock.restart();
}

void MyCanvas::OnUpdate(){
    // Clear screen
    RenderWindow::clear(sf::Color(0, 128, 0));

    // Rotate the sprite
    mySprite.rotate(myClock.getElapsedTime().asSeconds() * 100.f);

    // Draw it
    RenderWindow::draw(mySprite);
    myClock.restart();
}

//INCLUDES//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
#include "bullet.h"
#include <vector>
#include<math.h>
#include<cstdlib>
#include "player.h"

using sf::RenderWindow;
using sf::Keyboard;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2i;
//--------------------------------//

//CONSTRUCTOR//

MainWindow::MainWindow(){
    RenderWindow* wind = new RenderWindow(sf::VideoMode(800,600),"Hello");
    /*sf::RectangleShape rect;
    rect.setPosition(Vector2f(235,350));
    rect.setSize(Vector2f(30,30));
    rect.setFillColor(sf::Color(33,42,231,255));
    rect.setOrigin(Vector2f(15, 15));*/

    this->start(wind);
}

MainWindow::MainWindow(const MainWindow &m){
    this->player = Player::getInstance();
}
//--------------------------------//

//DESTRUCTOR//
MainWindow::~MainWindow(){

}
//--------------------------------//

//OPERATOR//
MainWindow &MainWindow::operator=(const MainWindow &m){
    if(&m != this){
        this->player = Player::getInstance();
    }
    return *this;
}
//--------------------------------//

//OTHERS//
void MainWindow::movePlayer(float x, float y){
    this->player->move(x, y);
}

void MainWindow::rotatePlayer(sf::RenderWindow* window)
{
    double a, b;
    Vector2i mouse;
    float angle;


    a = mouse.x - player->getOrigin().x;
    b = mouse.y - player->getOrigin().y;

    mouse = Mouse::getPosition(*window);
    angle = -atan2( a , b) * 180 / 3.14;
    this->player->rotate(angle);
}

Bullet b1;
std::vector<Bullet *> bullets;
int test=0;




void MainWindow::start(sf::RenderWindow* window){
    int mob = 5;
    int valx=10;
    int valy=10;

    while(window->isOpen()){
        sf::Event e;
        double a, b;
        float angle;

        Vector2f aimDir;
        Vector2f aimDirNorm;
        Vector2f playerCenter;

        while(window->pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window->close();
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Z)){
            this->movePlayer(0, -this->player->getSpeed());
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            this->movePlayer(0, this->player->getSpeed());
        }
        if(Keyboard::isKeyPressed(Keyboard::Q)){
            this->movePlayer(-this->player->getSpeed(), 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            this->movePlayer(this->player->getSpeed(), 0);
        }







        a = Mouse::getPosition(*window).x - player->getPosition().x;
        b = Mouse::getPosition(*window).y - player->getPosition().y;

        aimDir = Vector2f(a, b);
        aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

        angle = -atan2( a , b) * 180 / 3.14;
        this->player->rotate(angle);
        if(Mouse::isButtonPressed(Mouse::Left)==false){
            test=0;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
                {
            if(test%200==0){
                    b1.setShapePosition(player->getPosition());
                    b1.setCurrVelocity(aimDirNorm*b1.getMaxSpeed());

                    bullets.push_back(new Bullet(b1));
                    test++;
            }else{
                test++;}
                }

                for (size_t i = 0; i < bullets.size(); i++)
                {
                    bullets[i]->moveShape();

                    //Out of bounds
                    if (bullets[i]->getShape().getPosition().x < 0 || bullets[i]->getShape().getPosition().x > window->getSize().x
                        || bullets[i]->getShape().getPosition().y < 0 || bullets[i]->getShape().getPosition().y > window->getSize().y)
                    {
                        bullets.erase(bullets.begin() + i);

                    }
                    else
                    {
                        //Enemy collision
                        /*for (size_t k = 0; k < enemies.size(); k++)
                        {
                            if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
                            {
                                bullets.erase(bullets.begin() + i);
                                enemies.erase(enemies.begin() + k);
                                break;
                            }
                        }*/
                    }
                }




        if(mob==0){
            //sf::Thread thread(stopWave());
            //thread.launch();
        }
        mob++;

        window->clear();
        window->draw(this->player->getRect());
        for (size_t i = 0; i < bullets.size(); i++)
        {
            window->draw(bullets.at(i)->getShape());
        }

        for (size_t j = 0; j < enemies.size(); j++)
        {
            //std::cout<<j<<" test"<<std::endl;
            window->draw(this->enemies.at(j)->getRect());
        }
        window->display();
    }
}

void MainWindow::stopWave(){
    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();
    std::cout<<"DEBUT"<<std::endl;
    while(elapsed.asSeconds() != 30){

        elapsed = clock.getElapsedTime();
    }
    std::cout<<"FIN"<<std::endl;
}

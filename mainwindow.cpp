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
    int mob = 0;
    int valx=10;
    int valy=10;
    Vector2f previous;

    sf::Clock clock;
    sf::Time elapsed;

    while(window->isOpen()){
        sf::Event e;
        double a, b;
        float angle;

        Vector2f aimDir;
        Vector2f aimDirNorm;
        Vector2f playerCenter;

        while(window->pollEvent(e)){
            if(e.type==sf::Event::Closed){
                //tout détruire fdp
                window->close();
            }
        }

        //Sauvegarde de la position avant déplacement
        previous.x = this->player->getPosition().x;
        previous.y = this->player->getPosition().y;

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

        //Collision zombie
        double valX = this->player->getPosition().x ;
        double valY = this->player->getPosition().y ;
        for (int i=0;i<this->enemies.size();i++){
            if ((std::abs(valX - this->enemies.at(i)->getPosition().x ) < 32) &&
                    (std::abs(valY - this->enemies.at(i)->getPosition().y)) < 32)
            {
                this->player->setPosition(previous.x, previous.y);
            }
        }

        //Collision bord
        if ((this->player->getPosition().x-16)<0 || (this->player->getPosition().y-16)<0 || (this->player->getPosition().x+16) > 800 || (this->player->getPosition().y+16) >600){
            this->player->setPosition(previous.x, previous.y);
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
                test++;
            }
                }

                for (size_t i = 0; i < bullets.size(); i++)
                {
                    bullets[i]->moveShape();

                    //Out of bounds
                    if (bullets[i]->getShape().getPosition().x < 0 || bullets[i]->getShape().getPosition().x > window->getSize().x
                        || bullets[i]->getShape().getPosition().y < 0 || bullets[i]->getShape().getPosition().y > window->getSize().y)
                    {
                        bullets.erase(bullets.begin() + i);

                    }else if (this->enemies.size()>0){ //Collision zombie
                        double x = bullets[i]->getShape().getPosition().x;
                        double y = bullets[i]->getShape().getPosition().y;

                        for (int k=0;k<this->enemies.size();k++){
                            if ((std::abs(x - this->enemies.at(k)->getPosition().x ) < 16) &&
                                    (std::abs(y - this->enemies.at(k)->getPosition().y)) < 16){
                                bullets.erase(bullets.begin() + i);
                                break;
                            }
                        }

                    }
                }


        if(enemies.size()==0){
            elapsed = clock.getElapsedTime();
            if(elapsed.asSeconds() <= 15){
//                        std::cout<<"PAUSE"<<std::endl;
            }
            else {
                          //std::cout<<"SPAWN ZOMBIES"<<std::endl;
                          int calcul=20;
                          int localisation=0;
                          for(int i=0;i<calcul;i++){
                            localisation+=50;
                            enemies.push_back(new Enemy(32,32,localisation,localisation+20,0.1,100));
                          }
            }
        }

        window->clear();
        window->draw(this->player->getRect());
        for (size_t i = 0; i < bullets.size(); i++)
        {
            window->draw(bullets.at(i)->getShape());
        }

        for (size_t j = 0; j < enemies.size(); j++)
        {
            window->draw(this->enemies.at(j)->getRect());
        }
        window->display();
    }
}

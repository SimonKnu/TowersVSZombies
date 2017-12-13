//INCLUDES//
#include "mainwindow.h"

#include <iostream>
#include <math.h>
#include <cstdlib>

#include "SFML/Graphics.hpp"

#include "bullet.h"

using sf::RenderWindow;
using sf::Keyboard;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2i;
//--------------------------------//

        //CONSTRUCTOR//
MainWindow::MainWindow(){
    RenderWindow* wind = new RenderWindow(sf::VideoMode(800,600),"TowersVSZombies");

    this->start(wind);
}

MainWindow::MainWindow(const MainWindow &m){
    this->player = m.player;
    for(int i=0;i<m.enemies.size();i++){
        enemies.push_back(new Enemy(*m.enemies.at(i)));
    }
}
//--------------------------------//

        //DESTRUCTOR//
MainWindow::~MainWindow(){
    delete player;
    player=0;

    for(int i=0;i<enemies.size();i++){
        delete enemies.at(i);
        enemies.at(i)=0;
    }
    enemies.clear();
}
//--------------------------------//

            //OPERATOR//
MainWindow& MainWindow::operator=(const MainWindow &m){
    if(&m != this){
        this->player = m.player;
        for(int i=0;i<m.enemies.size();i++){
            enemies.push_back(new Enemy(*m.enemies.at(i)));
        }
    }
    return *this;
}
//--------------------------------//

            //OTHERS//
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
int test2=0;
bool moving=false;



void MainWindow::start(sf::RenderWindow* window){
    int manche=0;
    int mob=5;
    bool changementManche=true;

    Vector2f previous;
    Vector2f previousZombie;

    sf::Clock clock;
    sf::Time elapsed;

    while(window->isOpen()){
        sf::Event e;
        double a, b;
        float angle;

        Vector2f aimDir;
        Vector2f aimDirNorm;



        while(window->pollEvent(e)){
            if(e.type==sf::Event::Closed){
                //tout détruire
                window->close();
            }
        }

        //Sauvegarde de la position avant déplacement
        previous.x = this->player->getPosition().x;
        previous.y = this->player->getPosition().y;

        moving=false;

        //Permet de bouger le personnage à gauche/droite/bas/haut
        if(Keyboard::isKeyPressed(Keyboard::Z)){
            this->player->move(0, -this->player->getSpeed());
            moving=true;
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            this->player->move(0, this->player->getSpeed());
            moving=true;
        }
        if(Keyboard::isKeyPressed(Keyboard::Q)){
            this->player->move(-this->player->getSpeed(), 0);
            moving=true;
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            this->player->move(this->player->getSpeed(), 0);
            moving=true;
        }

        if(moving){
            if(test2<500){
                player->setTexture(1);
                test2++;
            }else if(test2<1000){
                player->setTexture(2);
                test2++;
            }else{
                test2=0;
            }
        }else{
            player->setTexture(0);
            test2=0;
        }


        //Collision bord
        if ((this->player->getPosition().x-32)<0 || (this->player->getPosition().y-32)<0 || (this->player->getPosition().x+32) > 800 || (this->player->getPosition().y+32) >600){
            this->player->setPosition(previous.x, previous.y);
        }

        //Collision zombie
        for (int i=0;i<this->enemies.size();i++){
            if ((std::abs(this->player->getPosition().x - this->enemies.at(i)->getPosition().x ) < 32) && (std::abs(this->player->getPosition().y  - this->enemies.at(i)->getPosition().y ) < 32)){
                this->player->setPosition(previous.x, previous.y);
            }

            previousZombie.x = enemies.at(i)->getPosition().x;
            previousZombie.y = enemies.at(i)->getPosition().y;

            //IA qui suit le joueur
            float dx = player->getPosition().x - enemies.at(i)->getPosition().x;
            float dy = player->getPosition().y - enemies.at(i)->getPosition().y;
            float length = sqrt( dx*dx + dy*dy );
            dx /= length;
            dy /= length; // normalize (make it 1 unit length) ---> Source : https://mike.newgrounds.com/news/post/265836 ---> PS : Il ressemble à Mr.Colmant
            dx *= 0.01; //0.1 = vitesse des zombies
            dy *= 0.01; //scale to our desired speed
            enemies.at(i)->move(dx,dy);

            if ((std::abs(this->player->getPosition().x - this->enemies.at(i)->getPosition().x ) < 32) && (std::abs(this->player->getPosition().y  - this->enemies.at(i)->getPosition().y ) < 32)){
                enemies.at(i)->setPosition(previousZombie.x, previousZombie.y);
            }
        }







        /*REVOIR LE CODE POUR L'OPTIMISER VICTOR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  (En dessous)*/
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

                    }
                    else if (this->enemies.size()>0){ //Collision zombie
                        double x = bullets[i]->getShape().getPosition().x;
                        double y = bullets[i]->getShape().getPosition().y;

                        for (int k=0;k<this->enemies.size();k++){
                            if ((std::abs(x - this->enemies.at(k)->getPosition().x ) < 32) &&(std::abs(y - this->enemies.at(k)->getPosition().y)) < 32){
                                bullets.erase(bullets.begin() + i);

                                this->enemies.at(k)->setHealth(25);//Dommage causé par la balle

                                if(this->enemies.at(k)->getHealth()<=0){
                                    this->enemies.erase(enemies.begin()+k);

                                    if(enemies.size()==0){
                                         clock.restart();           //On redémarre une manche
                                    }
                                }
                                break;
                            }
                        }

                    }
                }

   /*REVOIR LE CODE POUR L'OPTIMISER VICTOR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (Au dessus)*/


        //Système de manche avec un délai entre chaque manche
        if(enemies.size()==0){
            elapsed = clock.getElapsedTime();
            if(elapsed.asSeconds() <= 10){   //10 secondes de pause entre chaque manche
                if(changementManche){
                    manche+=1;               //On passe à la manche suivante -> Difficulté augmente
                    changementManche=false;
                }
            }
            else {
                mob += manche/2;            //On augmente le nombre mob en fonction de la manche, plus la manche est élevée, plus il y a des monstres

                int localisation=0; //A changer avec des spawner

                for(int i=0;i<mob;i++){
                    localisation+=40;
                    enemies.push_back(new Enemy(64,64,localisation+20,localisation+30,0.1,100));
                }
                changementManche=true;
            }
        }


        //Update de l'affichage de tous les élèments dans la fenetre
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

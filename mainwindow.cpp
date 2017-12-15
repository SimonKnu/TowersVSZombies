#include "mainwindow.h"

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "bullet.h"
#include "menu.h"

using sf::RenderWindow;
using sf::Keyboard;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2i;



//-----------------------------------------------------------------------//
                            //FORME CANONIQUE//

MainWindow::MainWindow(){
    RenderWindow* wind = new RenderWindow(sf::VideoMode(800,600),"TowersVSZombies");
    menus.push_back(new Menu("Start",400,100));
    menus.push_back(new Menu("About",400,300));
    menus.push_back(new Menu("Quit",400,500));

    this->start(wind);
}

MainWindow::~MainWindow(){
    delete player;
    player=0;

    for(int i=0;i<enemies.size();i++){
        delete enemies.at(i);
        enemies.at(i)=0;
    }
    enemies.clear();
}



//-----------------------------------------------------------------------//



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



//VICTOR BOUGE CA DE LA TU FAIS  CHIER  -> Ta bullet sert a rien en +, just saying
Bullet b1;
std::vector<Bullet *> bullets;
int test=0;
int test2=0;
bool moving=false;




void MainWindow::start(sf::RenderWindow* window){
    int manche=0;                           //Permet de compter le nombre de manches
    int mob=5;                              //Permet de savoir le nombre de montres à faire apparaitre
    bool changementManche=true;             //Permet de savoir si on change de manche pour déclancher la pause
    int pos;                                //Permet de déterminer la position du spawn des zombies


    Vector2f previous;
    Vector2f previousZombie;

    sf::Clock clock;
    sf::Time elapsed;
    sf::Time elapsedDamage;
    std::srand(std::time(0));

    //Pour les manches
    Menu menuManche("",400,300);
    //Affichage argent
    Menu menuMoney("",50,575);;

    bool launchGame = true;
    int compteurMenu=0;
    this->menus.at(compteurMenu)->changerColor(sf::Color::White);

    //Bar de vie
    sf::RectangleShape lifeBar(sf::Vector2f(150, 10));
    lifeBar.setFillColor(sf::Color::Red);
    lifeBar.setPosition(625,575);
    sf::RectangleShape lifeBar2(sf::Vector2f(0, 10));
    lifeBar2.setFillColor(sf::Color::White);
    lifeBar2.setPosition(775,575);

    int damageTime = 2; //temps(seconde) entre les degats



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


            //A AMELIORER, PAS BIEN CODER
            if(true == launchGame){
                if(e.type==sf::Event::KeyReleased){
                    if(e.key.code == sf::Keyboard::Z){
                        compteurMenu--;
                        if(compteurMenu<0){
                            compteurMenu = 2;
                        }
                        for(int i=0;i<3;i++){
                            if(i != compteurMenu){
                                this->menus.at(i)->changerColor(sf::Color::Red);
                            }
                            else {
                               this->menus.at(compteurMenu)->changerColor(sf::Color::White);
                            }
                        }
                    }
                    if(e.key.code == sf::Keyboard::S){
                        compteurMenu++;
                        if(compteurMenu>2){
                            compteurMenu = 0;
                        }

                        for(int i=0;i<3;i++){
                            if(i != compteurMenu){
                               this->menus.at(i)->changerColor(sf::Color::Red);
                            }
                            else {
                               this->menus.at(compteurMenu)->changerColor(sf::Color::White);
                            }
                        }
                    }
                    if(e.key.code == sf::Keyboard::Return){
                        switch (compteurMenu) {
                        case 0: launchGame=false;
                            break;
                        case 1:
                            break;
                        case 2: window->close();
                            break;
                        }
                    }
                }
            }
        }

        if(true == launchGame){
            window->clear();
            for(int i=0;i<3;i++){
                window->draw(menus.at(i)->getText());
            }
            window->display();
        }

        else {

            //Sauvegarde de la position du joueur avant déplacement
            previous.x = this->player->getPosition().x;
            previous.y = this->player->getPosition().y;

            //Compteur de secondes entre 2 dégats
            elapsedDamage = clock.getElapsedTime();

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
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                launchGame=true;
            }


            if(moving){
                if(test2<500){
                    player->setTexture(1);
                    test2++;
                }
                else if(test2<1000){
                    player->setTexture(2);
                    test2++;
                }
                else{
                    test2=0;
                }
            }
            else{
                player->setTexture(0);
                test2=0;
            }


            //Détection de la collision du joueur avec les bords
            if ((this->player->getPosition().x-32)<0 || (this->player->getPosition().y-32)<0 || (this->player->getPosition().x+32) > 800 || (this->player->getPosition().y+32) >600){
                this->player->setPosition(previous.x, previous.y);
            }

            //Gestion des zombie (déplacment, attaque)
            for (int i=0;i<this->enemies.size();i++){

                 //Détection de la collision du joeur
                if ((std::abs(this->player->getPosition().x - this->enemies.at(i)->getPosition().x ) < 32) && (std::abs(this->player->getPosition().y  - this->enemies.at(i)->getPosition().y ) < 32)){
                    //Retour a la posiition precedente
                    this->player->setPosition(previous.x, previous.y);
                }

                //Sauvegarde de la position du zombie avant déplacement
                previousZombie.x = enemies.at(i)->getPosition().x;
                previousZombie.y = enemies.at(i)->getPosition().y;

                // "INTELLIGENCE ARTIFICIELLE" DES ZOMBIES //
                //IA qui suit le joueur
                float enemyPlayerX = player->getPosition().x - enemies.at(i)->getPosition().x;
                float enemyPlayerY = player->getPosition().y - enemies.at(i)->getPosition().y;

                //IA qui vise la base
                float enemyBaseX = 800 - enemies.at(i)->getPosition().x;
                float enemyBaseY = 300 - enemies.at(i)->getPosition().y;

                //On calcul la distance pour savoir qui le zombie préfère viser (le plus pres en l'occurence)
                float lengthEnemyPlayer = sqrt( enemyPlayerX*enemyPlayerX + enemyPlayerY*enemyPlayerY );
                float lengthEnemyBase = sqrt( enemyBaseX*enemyBaseX + enemyBaseY*enemyBaseY );

                //Si la base est plus loin que le joueur -> Joueur, sinon -> Base
                if(lengthEnemyBase>lengthEnemyPlayer){
                    enemyPlayerX /= lengthEnemyPlayer;
                    enemyPlayerY /= lengthEnemyPlayer; // normalize (make it 1 unit length) ---> Source : https://mike.newgrounds.com/news/post/265836 ---> PS : Il ressemble à Mr.Colmant
                    enemyPlayerX *= 0.01; //0.1 = vitesse des zombies
                    enemyPlayerY *= 0.01; //scale to our desired speed
                    enemies.at(i)->move(enemyPlayerX,enemyPlayerY);
                }
                else {
                    enemyBaseX /= lengthEnemyBase;
                    enemyBaseY /= lengthEnemyBase;
                    enemyBaseX *= 0.01;
                    enemyBaseY *= 0.01;
                    enemies.at(i)->move(enemyBaseX,enemyBaseY);
                }

                //Détection de la collision d'un zombie
                if ((std::abs(this->player->getPosition().x - this->enemies.at(i)->getPosition().x ) < 32) && (std::abs(this->player->getPosition().y  - this->enemies.at(i)->getPosition().y ) < 32)){
                    //Retour a la posiition precedente
                    enemies.at(i)->setPosition(previousZombie.x, previousZombie.y);

                    //Attaque le joueur si un certain temps c'est ecoulé
                    if (elapsedDamage.asSeconds() > damageTime){
                        this->player->setHealth(this->player->getHealth()-enemies.at(i)->getDamage());
                        elapsedDamage = clock.restart();
                    }
                }
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


            if (Mouse::isButtonPressed(Mouse::Left)){
                if(test%200==0){
                        b1.setShapePosition(player->getPosition());
                        b1.setCurrVelocity(aimDirNorm*b1.getMaxSpeed());

                        bullets.push_back(new Bullet(b1));
                        test++;
                }
                else{
                    test++;
                }
            }


            for (size_t i = 0; i < bullets.size(); i++){
                 bullets[i]->moveShape();

                 //Détection de la collision de la balle avec les bords
                 if (bullets[i]->getShape().getPosition().x < 0 || bullets[i]->getShape().getPosition().x > window->getSize().x
                         || bullets[i]->getShape().getPosition().y < 0 || bullets[i]->getShape().getPosition().y > window->getSize().y)
                 {
                     bullets.erase(bullets.begin() + i);
                 }
                 else if (this->enemies.size()>0){ //Collision zombie
                     double x = bullets[i]->getShape().getPosition().x;
                     double y = bullets[i]->getShape().getPosition().y;

                     for (int k=0;k<this->enemies.size();k++){
                         //Détection de la collision de la balle avec un zombie
                         if ((std::abs(x - this->enemies.at(k)->getPosition().x ) < 32) &&(std::abs(y - this->enemies.at(k)->getPosition().y)) < 32){
                            bullets.erase(bullets.begin() + i);

                            this->enemies.at(k)->setHealth(25);//Dommage causé par la balle

                            if(this->enemies.at(k)->getHealth()<=0){
                                this->enemies.erase(enemies.begin()+k); //Suppression du zombie
                                this->player->setMoney(this->player->getMoney()+5); //Ajout du gain

                                if(enemies.size()==0){
                                    clock.restart();           //On redémarre une manche
                                }
                            }
                            break;
                        }
                    }
                }
            }




            //Système de manche avec un délai entre les différentes manches. Plus les manches augmentent, plus les zombies sont résistants et nombreux.
            if(enemies.size()==0){

                elapsed = clock.getElapsedTime();//Permet de connaitre le temps écouler depuis le lancement de la clock

                if(elapsed.asSeconds() <= 15){   //15 secondes de pause entre chaque manche
                    if(changementManche){
                        manche+=1;               //On passe à la manche suivante -> Difficulté augmente

                        std::stringstream ss;    //Permet de set le menu permettant d'afficher le nombre de manche à l'écran
                        ss<<"Wave "<<manche;
                        menuManche.changerText(ss.str());

                        changementManche=false;

                        this->player->setHealth(100);
                    }

                    //Permet d'afficher l'info sur la manche suivante à l'écran
                    window->clear();
                    window->draw(menuManche.getText());
                }
                else {
                    mob += manche/2;            //On augmente le nombre de zombies en fonction de la manche, plus la manche est élevée, plus il y a des zombies

                    int spawn = 0;
                    pos;
                    for(int i=0;i<mob;i++){
                        pos = std::rand()%5;    //On crée des "spawneur" ou les montres peuvent apparaitre
                        switch(pos){
                            case 0 : enemies.push_back(new Enemy(64,64,spawn,0,0.1,100,10));break;
                            case 1 : enemies.push_back(new Enemy(64,64,spawn-16,150,0.1,100,10));break;
                            case 2 : enemies.push_back(new Enemy(64,64,spawn-32,300,0.1,100,10));break;
                            case 3 : enemies.push_back(new Enemy(64,64,spawn-16,450,0.1,100,10));break;
                            case 4 : enemies.push_back(new Enemy(64,64,spawn,600,0.1,100,10));break;
                        }
                        spawn -= 32;            //On décrémente le spawn pour pas que les zombies spawn en étant collés
                    }
                    changementManche=true;
                }
            }


            //Update de l'affichage de tous les élèments dans la fenetre
            if(changementManche){
                window->clear();
            }

            //Affichage argent
            std::stringstream ss;
            ss<<this->player->getMoney()<<"$";
            menuMoney.changerText(ss.str());
            window->draw(menuMoney.getText());

            //Affichage bar de vie
            float lifeBarSize = this->player->getHealth()/100*150; //Calcul pour déterminer la taille de la barre de vie
            lifeBar.setSize(sf::Vector2f(lifeBarSize,10));
            window->draw(lifeBar);
            lifeBar2.setSize(sf::Vector2f(lifeBarSize-150,10));
            window->draw(lifeBar2);

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
}

void MainWindow::dessiner(sf::RenderWindow *window){

}


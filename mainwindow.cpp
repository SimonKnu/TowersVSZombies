#include "mainwindow.h"

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sstream>



//-----------------------------------------------------------------------//
                            //FORME CANONIQUE//

MainWindow::MainWindow(sf::RenderWindow* containeur):Containeur(containeur), menuWave("",sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2),menuMoney("",sf::VideoMode::getDesktopMode().width/16,sf::VideoMode::getDesktopMode().height/(600/575)-32){
    mapTexture.loadFromFile("map.png");
    map.setTexture(mapTexture);


    lifeBar =sf::RectangleShape(sf::Vector2f(sf::VideoMode::getDesktopMode().width/(80/15), sf::VideoMode::getDesktopMode().height/60));
    lifeBar.setFillColor(sf::Color::Red);
    lifeBar.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width/6*5,sf::VideoMode::getDesktopMode().height/(600/575)-32));

    lifeBar2 =sf::RectangleShape(sf::Vector2f(0, sf::VideoMode::getDesktopMode().height/60));
    lifeBar2.setFillColor(sf::Color::White);
    lifeBar2.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width/6*5+150,sf::VideoMode::getDesktopMode().height/(600/575)-32));
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



void MainWindow::rotatePlayer()
{
    sf::Vector2i mouse;

    double a = mouse.x - player->getOrigin().x;
    double b = mouse.y - player->getOrigin().y;

    mouse = sf::Mouse::getPosition(*Containeur::getWindow());
    float angle = -atan2( a , b) * 180 / 3.14;
    this->player->rotate(angle);
}

//Détection collision (joueur / zombie)
bool MainWindow::checkCollisionPlayerZombie(int index){
    if ((std::abs(this->player->getPosition().x - this->enemies.at(index)->getPosition().x ) < 32) && (std::abs(this->player->getPosition().y  - this->enemies.at(index)->getPosition().y ) < 32)){
        return true;
    }
    else{
        return false;
    }
}

//Détection collision (zombie / balle)
bool MainWindow::checkCollisionBulltetZombie(int indexZ, int indexB){
    if ((std::abs(bullets[indexB]->getShape().getPosition().x - this->enemies.at(indexZ)->getPosition().x ) < 32) &&(std::abs(bullets[indexB]->getShape().getPosition().y - this->enemies.at(indexZ)->getPosition().y)) < 32){
        return true;
    }
    else{
        return false;
    }
}



void MainWindow::drawElements(){
    int moving=0;

    sf::Vector2f previous;
    sf::Vector2f previousZombie;

    sf::Time elapsed;
    sf::Time elapsedDamage;
    sf::Time elapsedEnd;
    std::srand(std::time(0));

    int damageTime = 1; //temps(seconde) entre les degats


    //Sauvegarde de la position du joueur avant déplacement
    previous.x = this->player->getPosition().x;
    previous.y = this->player->getPosition().y;


    //Compteur de secondes entre 2 dégats
    elapsedDamage = clock.getElapsedTime();



    this->player->setMoving(false);

    //Permet de bouger le personnage à gauche/droite/bas/haut
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        this->player->move(0, -this->player->getSpeed());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->player->move(0, this->player->getSpeed());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        this->player->move(-this->player->getSpeed(), 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->player->move(this->player->getSpeed(), 0);
    }

    //Permet d'animer le personnage lorsqu'il marche
    if(player->getMoving()){
        if(moving<500){
            player->setTexture(1);
            moving++;
        }
        else if(moving<1000){
            player->setTexture(2);
            moving++;
        }
        else{
            moving=0;
        }
    }
    else{
        player->setTexture(0);
        moving=0;
    }


    //Détection de la collision du joueur avec les bords
    if (player->checkCollisionBorder()){
        this->player->setPosition(previous.x, previous.y);
    }

    //Gestion des zombie (déplacment, attaque)
    for (int i=0;i<this->enemies.size();i++){

        //Détection de la collision du joeur
        if (checkCollisionPlayerZombie(i)){
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
        float enemyBaseX = sf::VideoMode::getDesktopMode().width - enemies.at(i)->getPosition().x;
        float enemyBaseY = sf::VideoMode::getDesktopMode().height/2 - enemies.at(i)->getPosition().y;

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
        if (checkCollisionPlayerZombie(i)){
            //Retour a la posiition precedente
            enemies.at(i)->setPosition(previousZombie.x, previousZombie.y);

            //Attaque le joueur si un certain temps c'est ecoulé
            if (elapsedDamage.asSeconds() > damageTime){
                 this->player->setHealth(this->player->getHealth()-enemies.at(i)->getDamage());
                 elapsedDamage = clock.restart();
            }
        }
    }


    // "CALCULER LA POSITION DE LA SOURIS" (vers la souris) //
    //récupération de la position de la souris
    double a = sf::Mouse::getPosition(*Containeur::getWindow()).x - player->getPosition().x;
    double b = sf::Mouse::getPosition(*Containeur::getWindow()).y - player->getPosition().y;
    sf::Vector2f aimDir = sf::Vector2f(a, b);

    //calcule de l'angle de rotation afin de pointer vers la souris
    sf::Vector2f aimDirNorm;
    aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
    aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    float angle = -atan2( a , b) * 180 / 3.14;
    this->player->rotate(angle);

    // "GESTION DES PROJECTILES" /

    //Gestion de la "vitesse d'attaque" du personnage.
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)==false){
        numberBullet=0;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(numberBullet%200==0){
            b1.setShapePosition(player->getPosition());
            b1.setCurrVelocity(aimDirNorm*b1.getMaxSpeed());
            bullets.push_back(new Bullet(b1));
            numberBullet++;
        }
        else{
            numberBullet++;
        }
    }

    //Mouvement des projectiles
    for (size_t i = 0; i < bullets.size(); i++){
        bullets[i]->moveShape();

        //Détection de la collision de la balle avec les bords
        if (bullets[i]->checkCollisionBorder()){
             bullets.erase(bullets.begin() + i);
        }
        else if (this->enemies.size()>0){ //Collision zombie

            for (int k=0;k<this->enemies.size();k++){
                //Détection de la collision de la balle avec un zombie
                if (checkCollisionBulltetZombie(k,i)){
                    bullets.erase(bullets.begin() + i);

                    this->enemies.at(k)->setHealth(25);//Dommage causé par la balle

                    if(this->enemies.at(k)->getHealth()<=0){
                        this->enemies.erase(enemies.begin()+k); //Suppression du zombie
                        this->player->setMoney(5); //Ajout du gain

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
            if(changeWave){
                wave+=1;               //On passe à la manche suivante -> Difficulté augmente

                std::stringstream ss;    //Permet de set le menu permettant d'afficher le nombre de manche à l'écran
                ss<<"Wave "<<wave;
                menuWave.changerText(ss.str());

                changeWave=false;
            }
            //Permet d'afficher l'info sur la manche suivante à l'écran
            Containeur::getWindow()->clear();
            Containeur::getWindow()->draw(menuWave.getText());
        }
        else {
            mob += wave/2;            //On augmente le nombre de zombies en fonction de la manche, plus la manche est élevée, plus il y a des zombies

            int spawn = 0;
            for(int i=0;i<mob;i++){
                posSpawn = std::rand()%5;    //On crée des "spawneur" ou les montres peuvent apparaitre
                switch(posSpawn){
                    case 0 : enemies.push_back(new Enemy(64,64,spawn,0,0.1,100,10));break;
                    case 1 : enemies.push_back(new Enemy(64,64,spawn-16,150,0.1,100,10));break;
                    case 2 : enemies.push_back(new Enemy(64,64,spawn-32,300,0.1,100,10));break;
                    case 3 : enemies.push_back(new Enemy(64,64,spawn-16,450,0.1,100,10));break;
                    case 4 : enemies.push_back(new Enemy(64,64,spawn,600,0.1,100,10));break;
                }
                spawn -= 32;            //On décrémente le spawn pour pas que les zombies spawn en étant collés
            }
            changeWave=true;
        }
    }
    for(int i=0;i<enemies.size();i++){
        a = player->getPosition().x - enemies.at(i)->getPosition().x;
        b = player->getPosition().y - enemies.at(i)->getPosition().y;
        sf::Vector2f aimDir = sf::Vector2f(a, b);

        //calcule de l'angle de rotation afin de pointer vers la souris
        sf::Vector2f aimDirNorm;
        aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

        float angle = -atan2( a , b) * 180 / 3.14;
        enemies.at(i)->rotate(angle);
    }


    //Update de l'affichage de tous les élèments dans la fenetre
    if(changeWave){
        Containeur::getWindow()->clear();
    }
    //map.setTexture(mapTexture);
    //map.setScale(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    //map.setScale(1.759853345554, 1);
    float tailleX=sf::VideoMode::getDesktopMode().width;
    float tailleY=sf::VideoMode::getDesktopMode().height;
    float scaleX=tailleX/1920;
    float scaleY=tailleY/1080;
    map.setScale(scaleX, scaleY);
    Containeur::getWindow()->draw(this->map);

    //Affichage argent
    std::stringstream ss;
    ss<<this->player->getMoney()<<" $";
    menuMoney.changerText(ss.str());
    Containeur::getWindow()->draw(menuMoney.getText());

    //Affichage bar de vie
    float lifeBarSize = this->player->getHealth()/100*150; //Calcul pour déterminer la taille de la barre de vie

    lifeBar.setSize(sf::Vector2f(lifeBarSize, 10));
    Containeur::getWindow()->draw(lifeBar);

    lifeBar2.setSize(sf::Vector2f(lifeBarSize-150,10));
    Containeur::getWindow()->draw(lifeBar2);

    Containeur::getWindow()->draw(this->player->getRect());

    for (size_t i = 0; i < bullets.size(); i++){
        Containeur::getWindow()->draw(bullets.at(i)->getShape());
    }

    for (size_t j = 0; j < enemies.size(); j++){
        Containeur::getWindow()->draw(this->enemies.at(j)->getRect());
    }

    //Fin de jeu
    if(this->player->getHealth()<=0){
        this->player->setFinalWave(wave);
        endgame=true;
    }

}


int MainWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Escape){
        return 3;
    }
    if(endgame){
        return 4;
    }
    return 1;
}




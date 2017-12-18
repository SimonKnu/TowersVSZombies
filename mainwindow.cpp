#include "mainwindow.h"

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sstream>

//********************************************************************************//

MainWindow::MainWindow(sf::RenderWindow* containeur):Containeur(containeur)
{
    mapTexture.loadFromFile("map.png");
    map.setTexture(mapTexture);

    menuWave = new Menu("",1080/2,720/(600/50)-32);
    menuMoney= new Menu("0 $",1080/16,720/(600/50)-32);
    menuReload= new Menu("Amo : 30/30",1080/8,720/(600/575)-32);
    menuHealth= new Menu("Health : ",1080/8*5+150-50,720/(600/50)-32);
    menuBase= new Menu("Base : ",1080/8*5+150-50,720/(600/575)-32);
    menuTurret= new Menu("",540,360);


    lifeBar = new sf::RectangleShape(sf::Vector2f(1080/(80/15), 720/60));
        lifeBar->setFillColor(sf::Color::Red);
        lifeBar->setPosition(sf::Vector2f(1080/8*5+150,720/(600/50)-32));
    lifeBar2 = new sf::RectangleShape(sf::Vector2f(0, 720/60));
        lifeBar2->setFillColor(sf::Color::Black);
        lifeBar2->setPosition(sf::Vector2f(1080/8*5+150+150,720/(600/50)-32));


    lifeBase = new sf::RectangleShape(sf::Vector2f(1080/(80/15), 720/60));
        lifeBase->setFillColor(sf::Color::Red);
        lifeBase->setPosition(sf::Vector2f(1080/8*5+150,720/(600/575)-32));
    lifeBase2 = new sf::RectangleShape(sf::Vector2f(0, 720/60));
        lifeBase2->setFillColor(sf::Color::Black);
        lifeBase2->setPosition(sf::Vector2f(1080/8*5+150+150,720/(600/575)-32));

    sound->addFile("hitmarker.wav");
    sound->addFile("damage.wav");
    sound->addFile("shot.wav");
    sound->addFile("reload.wav");
    sound->addFile("wave.wav");
    sound->loop(4);
}

MainWindow::MainWindow(const MainWindow &window):Containeur(window){
    map = window.map;

    sound = window.sound;
    player = window.player;

    menuWave = window.menuWave;
    menuMoney = window.menuMoney;
    menuReload = window.menuReload;
    menuHealth = window.menuHealth;
    menuBase = window.menuBase;
    menuTurret = window.menuTurret;

    lifeBar = window.lifeBar;
    lifeBar2 = window.lifeBar2;
    lifeBase = window.lifeBase;
    lifeBase2 = window.lifeBase2;

    wave = window.wave;
    mob = window.mob;
    changeWave = window.changeWave;
    posSpawn = window.posSpawn;
    numberBullet = window.numberBullet;
    reload = window.reload;
    pressA = window.pressA;
    healthBase = window.healthBase;
    movingAnimation = window.movingAnimation;

    for(int i=0;i<numberBulletTower.size();i++){
        numberBulletTower.push_back(window.numberBulletTower.at(i));
    }
    for(int i=0;i<turretAnimation.size();i++){
        turretAnimation.push_back(turretAnimation.at(i));
    }
    for(int i=0;i<ennemyAnimation.size();i++){
        ennemyAnimation.push_back(window.ennemyAnimation.at(i));
    }

    clock = window.clock;
    clockReload = window.clockReload;
    clockTurret = window.clockTurret;

    for(int i=0;i<enemies.size();i++){
        enemies.push_back(new Enemy(*window.enemies.at(i)));
    }
    for(int i=0;i<bullets.size();i++){
        bullets.push_back(new Bullet(*window.bullets.at(i)));
    }
    for(int i=0;i<towers.size();i++){
        towers.push_back(new Tower(*window.towers.at(i)));
    }
    b1 = window.b1;
}


MainWindow::~MainWindow(){
    delete player;
    player = 0;
    delete sound;
    sound = 0;

    delete menuReload;
    menuReload = 0;
    delete menuWave;
    menuWave = 0;
    delete menuMoney;
    menuMoney = 0;
    delete menuHealth;
    menuHealth = 0;
    delete menuBase;
    menuBase = 0;
    delete menuTurret;
    menuTurret = 0;

    delete lifeBase;
    lifeBase = 0;
    delete lifeBase2;
    lifeBase2 = 0;

    delete lifeBar;
    lifeBar = 0;
    delete lifeBar2;
    lifeBar2 = 0;


    for(int i=0;i<enemies.size();i++){
        delete enemies.at(i);
        enemies.at(i)=0;
    }
    enemies.clear();

    for(int i=0;i<bullets.size();i++){
        delete bullets.at(i);
        bullets.at(i)=0;
    }
    bullets.clear();

    for(int i=0;i<towers.size();i++){
        delete towers.at(i);
        towers.at(i)=0;
    }
    towers.clear();
}

MainWindow& MainWindow::operator=(const MainWindow& window){
    if(this!=&window){
        Containeur::operator=(window);
        map = window.map;

        sound = window.sound;
        player = window.player;

        menuWave = window.menuWave;
        menuMoney = window.menuMoney;
        menuReload = window.menuReload;
        menuHealth = window.menuHealth;
        menuBase = window.menuBase;
        menuTurret = window.menuTurret;

        lifeBar = window.lifeBar;
        lifeBar2 = window.lifeBar2;
        lifeBase = window.lifeBase;
        lifeBase2 = window.lifeBase2;

        wave = window.wave;
        mob = window.mob;
        changeWave = window.changeWave;
        posSpawn = window.posSpawn;
        numberBullet = window.numberBullet;
        reload = window.reload;
        pressA = window.pressA;
        healthBase = window.healthBase;
        movingAnimation = window.movingAnimation;

        for(int i=0;i<numberBulletTower.size();i++){
            numberBulletTower.push_back(window.numberBulletTower.at(i));
        }
        for(int i=0;i<turretAnimation.size();i++){
            turretAnimation.push_back(turretAnimation.at(i));
        }
        for(int i=0;i<ennemyAnimation.size();i++){
            ennemyAnimation.push_back(window.ennemyAnimation.at(i));
        }

        clock = window.clock;
        clockReload = window.clockReload;
        clockTurret = window.clockTurret;

        for(int i=0;i<enemies.size();i++){
            enemies.push_back(new Enemy(*window.enemies.at(i)));
        }
        for(int i=0;i<bullets.size();i++){
            bullets.push_back(new Bullet(*window.bullets.at(i)));
        }
        for(int i=0;i<towers.size();i++){
            towers.push_back(new Tower(*window.towers.at(i)));
        }
        b1 = window.b1;
    }
    return *this;
}

//********************************************************************************//

void MainWindow::drawElements(){
    sf::Time elapsed;
    sf::Time elapsedDamage;
    sf::Time elapsedReload;
    sf::Time elapsedTurret;

    std::srand(std::time(0));

    int damageTime = 1; //temps(seconde) entre les degats

    //Sauvegarde de la position du joueur avant déplacement
    this->player->setPreviousPosition();

    //Compteur de secondes entre 2 dégats
    elapsedDamage = clock.getElapsedTime();
    elapsedReload = clockReload.getElapsedTime();
    elapsedTurret = clockTurret.getElapsedTime();


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
    //Permet de recharger l'arme du player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        if(reload!=0){
            clockReload.restart();
            reload=0;
            sound->play(3);
        }
    }

    //Permet de sécurisé l'appel de drone (1 pression = un appel)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)==false){
            pressA=false;
    }

    //Permet d'appeler un drone (maximum 10 drones, 1 drone coute 250$)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            if(pressA==false){
                if(towers.size()<10){
                    if(player->getMoney()>=250){
                        int orientX;
                        int orientY;

                        checkOrientPlayer(&orientX, &orientY);

                        int posXTower = player->getPosition().x+orientX;
                        int posYTower = player->getPosition().y+orientY;
                        Tower* t1 = new Tower(64, 64, posXTower, posYTower);
                        if(!checkCollisionPlayerTurret(t1)){
                            towers.push_back(t1);
                            numberBulletTower.push_back(0);
                            turretAnimation.push_back(0);
                            player->setMoney(-250);
                        }
                        pressA=true;
                    }else{
                        clockTurret.restart();
                        menuTurret->changerText("No enough money to call a drone");
                    }
                }else{
                    clockTurret.restart();
                    menuTurret->changerText("Too many drones called");
                }
            }
    }

    //permet de désafficher le message d'erreur en rapport avec les drones aprés 3 secondes
    if(elapsedTurret.asSeconds()>3){
        menuTurret->changerText("");
    }

    //Permet d'animer le personnage lorsqu'il marche
    if(player->getMoving()){
        if(movingAnimation<250){
            player->setTexture(1);
            movingAnimation++;
        }
        else if(movingAnimation<500){
            player->setTexture(2);
            movingAnimation++;
        }
        else{
            movingAnimation=0;
        }
    }
    else{
        player->setTexture(0);
        movingAnimation=0;
    }

    //Détection de la collision du joueur avec les bords
    if (player->checkCollisionBorder()){
        this->player->goBack();
    }

    float destroyBaseX = 1080 -10;
    float destroyBaseY = 720/2 -10;

    //Gestion des zombie (déplacment, attaque)
    for (int i=0;i<this->enemies.size();i++){

        //Détection de la collision du joeur
        if (checkCollisionPlayerZombie(i)){
            //Retour a la posiition precedente
            this->player->goBack();
        }

        //Sauvegarde de la position du zombie avant déplacement
        enemies.at(i)->setPreviousPosition();

        // "INTELLIGENCE ARTIFICIELLE" DES ZOMBIES //
        //IA qui suit le joueur
        float enemyPlayerX = player->getPosition().x - enemies.at(i)->getPosition().x;
        float enemyPlayerY = player->getPosition().y - enemies.at(i)->getPosition().y;

        //IA qui vise la base
        float enemyBaseX = 1080 - enemies.at(i)->getPosition().x;
        float enemyBaseY = 720/2 - enemies.at(i)->getPosition().y;

        //On calcul la distance pour savoir qui le zombie préfère viser (le plus pres en l'occurence)
        float lengthEnemyPlayer = sqrt( enemyPlayerX*enemyPlayerX + enemyPlayerY*enemyPlayerY );
        float lengthEnemyBase = sqrt( enemyBaseX*enemyBaseX + enemyBaseY*enemyBaseY );

        //Si la base est plus loin que le joueur -> Joueur, sinon -> Base
        if(lengthEnemyBase>lengthEnemyPlayer){
            enemyPlayerX /= lengthEnemyPlayer;
            enemyPlayerY /= lengthEnemyPlayer;  // normalize (make it 1 unit length)
            //Source : https://mike.newgrounds.com/news/post/265836 ---> #Colmant


            //Permet de calculer l'angle pour rotate les zombies vers le joueur
            float angle = -atan2( enemyPlayerX , enemyPlayerY) * 180 / 3.14;
            enemies.at(i)->rotate(angle);

            enemyPlayerX *= 0.12;               //0.12 = vitesse des zombies
            enemyPlayerY *= 0.12;               //scale to our desired speed
            enemies.at(i)->move(enemyPlayerX,enemyPlayerY);
        }
        else {
            //Même chose qu'au dessus mais pour la base cette fois
            enemyBaseX /= lengthEnemyBase;
            enemyBaseY /= lengthEnemyBase;

            float angle = -atan2( enemyBaseX, enemyBaseY) * 180 / 3.14;
            enemies.at(i)->rotate(angle);

            enemyBaseX *= 0.12;
            enemyBaseY *= 0.12;
            enemies.at(i)->move(enemyBaseX,enemyBaseY);
        }

        for (int z=0;z<this->enemies.size();z++){
            //Détection de la collision d'un zombie avec un autre zombie
            if(checkCollisionZombieZombie(i,z) && i != z){
                //Retour a la posiition precedente
                enemies.at(i)->goBack();
            }
        }

        //Détection de la collision d'un zombie avec le joueur
        if (checkCollisionPlayerZombie(i)){
            //Retour a la posiition precedente
            enemies.at(i)->goBack();

            //Attaque le joueur si un certain temps c'est ecoulé
            if (elapsedDamage.asSeconds() > damageTime){
                 sound->play(1);
                 this->player->setHealth(this->player->getHealth()-enemies.at(i)->getDamage());
                 elapsedDamage = clock.restart();
            }
        }
    }

        //Calcul de la visée (orientation) des drones (attaque l'ennemie le plus proche dans un rayon de 250px)
        for(int i=0; i<towers.size(); i++){
            float dist=999999999*999999999;
            float distEnemy;
            int num;
            float towerEnemyX;
            float towerEnemyY;
            for(int j=0; j<enemies.size();j++){
                //on récupére la distance entre la tourelle et le zombie j
                towerEnemyX = enemies.at(j)->getPosition().x - towers.at(i)->getPosition().x;
                towerEnemyY = enemies.at(j)->getPosition().y - towers.at(i)->getPosition().y;
                distEnemy = sqrt( towerEnemyX*towerEnemyX + towerEnemyY*towerEnemyY );

                //si la distance est plus petite que celle sauvegardée, on la remplace
                if(distEnemy<dist){
                    dist=distEnemy;
                    num=j;
                }
            }

            //Si le zombie le plus proche est à moins de 250px, on oriente le drone vers celui ci et on commence à faire feu
            if(dist<=250){
                towerEnemyX/=dist;
                towerEnemyY/=dist;
                sf::Vector2f towerEnemy;
                towerEnemy.x=towerEnemyX;
                towerEnemy.y=towerEnemyY;

                float angle = -atan2(towerEnemyX, towerEnemyY)*180/3.14;
                towers.at(i)->rotate(angle);

                if(numberBulletTower.at(i)%750==0){
                    b1.setShapePosition(towers.at(i)->getPosition());
                    b1.setCurrVelocity(towerEnemy*b1.getMaxSpeed());
                    bullets.push_back(new Bullet(b1));
                    numberBulletTower.at(i)++;
                }else{
                    numberBulletTower.at(i)++;
                }
            }
        }

    //Supprime zombie s'il est dans la base
    //On parcourt le vector à l'envers pour éviter tout problème
    if(enemies.empty() == false) {
        for(int k = enemies.size() - 1; k >= 0; k--) {
            if(enemies.at(k)->getPosition().x >= destroyBaseX   &&   enemies.at(k)->getPosition().y >= destroyBaseY){
                enemies.erase( enemies.begin() + k );

                healthBase-=10;

                if(healthBase<=0){
                    player->setHealth(0);
                }

                if(enemies.size()==0){
                    clock.restart();
                }
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

    //Gestion des tirs et du rechargement
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(reload<30){
            if(elapsedReload.asSeconds()>3){
                if(numberBullet%200==0){
                    reload+=1;
                    sound->play(2);

                    b1.setShapePosition(player->getPosition());
                    b1.setCurrVelocity(aimDirNorm*b1.getMaxSpeed());
                    bullets.push_back(new Bullet(b1));
                    numberBullet++;
                }
                else{
                    numberBullet++;
                }
            }

        }
        else {
            sound->play(3);
            clockReload.restart();
            reload=0;
        }
    }

    //Mouvement des projectiles
    for (size_t i = 0; i < bullets.size(); i++){
        bullets[i]->moveShape();

        //Détection de la collision de la balle avec les bords
        if (bullets[i]->checkCollisionBorder()){
             bullets.erase(bullets.begin() + i);
        }
        else if (this->enemies.size()>0){   //Collision zombie

            for (int k=0;k<this->enemies.size();k++){
                //Détection de la collision de la balle avec un zombie
                if (checkCollisionBulltetZombie(k,i)){
                    bullets.erase(bullets.begin() + i);
                    sound->play(0);


                    this->enemies.at(k)->setHealth(25);         //Dommage causé par la balle

                    if(this->enemies.at(k)->getHealth()<=0){
                        this->enemies.erase(enemies.begin()+k); //Suppression du zombie
                        this->player->setMoney(5);              //Ajout du gain

                        if(enemies.size()==0){
                            clock.restart();                    //On redémarre une manche
                        }
                    }
                    break;
                }
            }
        }
    }


    //redimensionnage de la map
    float tailleX=1080;
    float tailleY=720;
    float scaleX=tailleX/1920;
    float scaleY=tailleY/1080;
    map.setScale(scaleX, scaleY);
    Containeur::getWindow()->draw(this->map);


    //Système de manche avec un délai entre les différentes manches. Plus les manches augmentent, plus les zombies sont résistants et nombreux.
    if(enemies.size()==0){
        sound->pause(4);
        elapsed = clock.getElapsedTime();   //Permet de connaitre le temps écouler depuis le lancement de la clock

        if(elapsed.asSeconds() <= 5){       //5 secondes de pause entre chaque manche
            if(changeWave){
                wave+=1;                    //On passe à la manche suivante -> Difficulté augmente

                std::stringstream ss;       //Permet de set le menu permettant d'afficher le nombre de manche à l'écran
                ss<<"Wave "<<wave;
                menuWave->changerText(ss.str());

                changeWave=false;
            }
            //Permet d'afficher l'info sur la manche suivante à l'écran
            Containeur::getWindow()->clear();
            Containeur::getWindow()->draw(this->map);
            Containeur::getWindow()->draw(menuWave->getText());
        }
        else {
            sound->play(4);
            mob += wave/2;            //On augmente le nombre de zombies en fonction de la manche, plus la manche est élevée, plus il y a des zombies

            int spawn = 0;
            for(int i=0;i<mob;i++){
                posSpawn = std::rand()%5;    //On crée des "spawneur" ou les montres peuvent apparaitre
                switch(posSpawn){
                    case 0 : enemies.push_back(new Enemy(64,64,spawn,0,0.15,100,10));break;
                    case 1 : enemies.push_back(new Enemy(64,64,spawn-16,150,0.15,100,10));break;
                    case 2 : enemies.push_back(new Enemy(64,64,spawn-32,300,0.15,100,10));break;
                    case 3 : enemies.push_back(new Enemy(64,64,spawn-16,450,0.15,100,10));break;
                    case 4 : enemies.push_back(new Enemy(64,64,spawn,600,0.15,100,10));break;
                }
                ennemyAnimation.push_back(0);
                spawn -= 48;            //On décrémente le spawn pour pas que les zombies spawn en étant collés
            }
            changeWave=true;
        }
    }



    //Update de l'affichage de tous les élèments dans la fenetre
    if(changeWave){
        Containeur::getWindow()->clear();
        Containeur::getWindow()->draw(this->map);
    }

    //affichage du potentiel message d'erreur concernant les drones
    Containeur::getWindow()->draw(menuTurret->getText());

    if(elapsedReload.asSeconds()>3){
        std::stringstream ss;
        ss<<"Amo : "<<30-reload<<"/30";
        menuReload->changerText(ss.str());
    }
    else {
        menuReload->changerText("Amo : Reloading...");
    }


    //Affichage de l'argent
    std::stringstream ss;
    ss<<this->player->getMoney()<<" $";
    menuMoney->changerText(ss.str());
    Containeur::getWindow()->draw(menuMoney->getText());

    ss.str();

    //Affichage des balles restantes/du rechargement en cours
    Containeur::getWindow()->draw(menuReload->getText());


    //Affichage barre de vie du joueur
    Containeur::getWindow()->draw(menuHealth->getText());
    float lifeBarSize = this->player->getHealth()/100*150; //Calcul pour déterminer la taille de la barre de vie
    lifeBar->setSize(sf::Vector2f(lifeBarSize, 10));
    lifeBar2->setSize(sf::Vector2f(lifeBarSize-150,10));

    Containeur::getWindow()->draw(*lifeBar);
    Containeur::getWindow()->draw(*lifeBar2);


    //Affichage de la barre de vie de la base
    float lifeBarBase = healthBase/100*150; //Calcul pour déterminer la taille de la barre de vie de la base
    Containeur::getWindow()->draw(menuBase->getText());
    lifeBase->setSize(sf::Vector2f(lifeBarBase, 10));
    lifeBase2->setSize(sf::Vector2f(lifeBarBase-150,10));
    Containeur::getWindow()->draw(*lifeBase);
    Containeur::getWindow()->draw(*lifeBase2);

    //Affichage du joueur
    Containeur::getWindow()->draw(this->player->getRect());

    //Affichage des balles
    for (size_t i = 0; i < bullets.size(); i++){
        Containeur::getWindow()->draw(bullets.at(i)->getShape());
    }

    //Affichage des ennemy et gestion de l'animation de ceux ci
    for (size_t j = 0; j < enemies.size(); j++){
        if(ennemyAnimation.at(j)==250){
            enemies.at(j)->changeAnimation();
            ennemyAnimation.at(j)=0;
        }
        ennemyAnimation.at(j)++;
        Containeur::getWindow()->draw(this->enemies.at(j)->getRect());
    }

    //Affichage des drones et gestion de l'animation de ceux ci
    for (size_t k = 0; k < towers.size(); k++){
        if(turretAnimation.at(k)==100){
            towers.at(k)->changeAnimation();
            turretAnimation.at(k)=0;
        }
        turretAnimation.at(k)++;
        Containeur::getWindow()->draw(this->towers.at(k)->getSprite());
    }

    //On vérifie que le joueur est toujours en vie. Si ce n'est pas le cas, on arrete la partie et on enregistre la dernière manche
    if(this->player->getHealth()<=0){
        this->player->setFinalWave(wave);
    }

}

int MainWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Escape){
        return 3;           //On est dirigé vers la page "wait"
    }
    return 1;               //On reste sur cette page tant qu'il ne se passe rien
}

//********************************************************************************//

//Permet d'orienter le joueur vers la position souris
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

//Permet d'empécher le joueur de poser un drone sur un autre (gestion de collision entre drones)
bool MainWindow::checkCollisionPlayerTurret(Tower * t1){
    for(int i=0; i<towers.size();i++){
        if ((std::abs(t1->getPosition().x - towers.at(i)->getPosition().x ) < 32) && (std::abs(t1->getPosition().y - towers.at(i)->getPosition().y ) < 32)){
            return true;
        }
    }
    return false;
}

//Méthode permetant au joueur de poser correctement les drones en fonction de son orientation (N,S,W,E)
void MainWindow::checkOrientPlayer(int *orientX, int *orientY)
{
    if(player->getRotate()>=0 && player->getRotate()<45 || player->getRotate()>=315 && player->getRotate()<360){
        *orientX=0;
        *orientY=64;
    }else if(player->getRotate()>=45 && player->getRotate()<135){
        *orientX=-64;
        *orientY=0;
    }else if(player->getRotate()>=135 && player->getRotate()<225){
        *orientX=0;
        *orientY=-64;
    }else{
        *orientX=64;
        *orientY=0;
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

//Détection collision (zombie / zombie)
bool MainWindow::checkCollisionZombieZombie(int indexA, int indexB){
    if ((std::abs(this->enemies.at(indexA)->getPosition().x  - this->enemies.at(indexB)->getPosition().x ) < 32) && (std::abs(this->enemies.at(indexA)->getPosition().y   - this->enemies.at(indexB)->getPosition().y ) < 32)){
        return true;
    }
    else{
        return false;
    }
}

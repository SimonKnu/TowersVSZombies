#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "containeur.h"
#include "player.h"
#include "enemy.h"
#include "menu.h"
#include "bullet.h"

#include <SFML/Graphics.hpp>

class MainWindow : public Containeur
{

    public:
        MainWindow(sf::RenderWindow* containeur);
        ~MainWindow();

        void rotatePlayer();
        void start();
        bool checkCollisionPlayerZombie(int index);
        bool checkCollisionBulltetZombie(int indexZ, int indexB);

        void drawElements();
        int chosenMenu(sf::Event e);

    private:
        Player *player = Player::getInstance();

        Menu menuWave;
        Menu menuMoney;

        sf::RectangleShape lifeBar;
        sf::RectangleShape lifeBar2;

        bool endgame =false;                    //Permet de savoir si la game est terminée (Joueur mort ou base morte)
        int wave=0;                           //Permet de compter le nombre de manches
        int mob=5;                              //Permet de savoir le nombre de montres à faire apparaitre
        bool changeWave=true;             //Permet de savoir si on change de manche pour déclancher la pause
        int posSpawn;                                //Permet de déterminer la position du spawn des zombies
        int numberBullet=0;                     //Permet de limiter le nombre de balles tirées

        sf::Clock clock;                        //Timer

        std::vector<Enemy *> enemies;
        std::vector<Bullet *> bullets;
        Bullet b1;

        sf::Texture mapTexture;
        sf::Sprite map;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "containeur.h"
#include "player.h"
#include "enemy.h"
#include "menu.h"
#include "bullet.h"
#include "sound.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainWindow : public Containeur
{

    public:
        MainWindow(sf::RenderWindow* containeur);
        ~MainWindow();

        void rotatePlayer();
        void start();
        bool checkCollisionPlayerZombie(int index);
        bool checkCollisionBulltetZombie(int indexZ, int indexB);
        bool checkCollisionZombieZombie(int indexA, int indexB);

        void drawElements();
        int chosenMenu(sf::Event e);

    private:
        Player *player = Player::getInstance();
        Sound *sound = Sound::getInstance();

        Menu *menuReload;
        Menu *menuWave;
        Menu *menuMoney;
        Menu *menuHealth;

        sf::RectangleShape *lifeBase;
        sf::RectangleShape *lifeBase2;

        sf::RectangleShape *lifeBar;
        sf::RectangleShape *lifeBar2;

        int wave=0;                           //Permet de compter le nombre de manches
        int mob=5;                              //Permet de savoir le nombre de montres à faire apparaitre
        bool changeWave=true;             //Permet de savoir si on change de manche pour déclancher la pause
        int posSpawn;                                //Permet de déterminer la position du spawn des zombies
        int numberBullet=0;                     //Permet de limiter le nombre de balles tirées
        int reload=0;
        float healthBase=100;

        sf::Clock clock;                        //Timer
        sf::Clock clockReload;

        std::vector<Enemy *> enemies;
        std::vector<Bullet *> bullets;
        Bullet b1;

        sf::Texture mapTexture;
        sf::Sprite map;

        sf::SoundBuffer buffer;
        std::vector< sf::Sound> sounds;

};

#endif // MAINWINDOW_H

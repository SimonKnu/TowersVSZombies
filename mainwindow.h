#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "containeur.h"
#include "player.h"
#include "enemy.h"
#include "menu.h"
#include "bullet.h"
#include "sound.h"
#include "tower.h"

#include <SFML/Graphics.hpp>

class MainWindow : public Containeur
{

    public:
        MainWindow(sf::RenderWindow* containeur);
        MainWindow(const MainWindow &window);
        ~MainWindow();
        MainWindow& operator=(const MainWindow& window);

        void rotatePlayer();
        void start();
        bool checkCollisionPlayerZombie(int index);
        bool checkCollisionPlayerTurret(Tower *);
        bool checkCollisionBulltetZombie(int indexZ, int indexB);
        bool checkCollisionZombieZombie(int indexA, int indexB);

        void checkOrientPlayer(int* orientX, int* orientY);

        void drawElements();
        int chosenMenu(sf::Event e);

    private:
        Player *player = Player::getInstance();
        Sound *sound = Sound::getInstance();

        Menu *menuReload;
        Menu *menuWave;
        Menu *menuMoney;
        Menu *menuHealth;
        Menu *menuBase;

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
        std::vector<int> numberBulletTower;
        bool pressA=false;
        std::vector<int> turretAnimation;
        std::vector<int> ennemyAnimation;
        int movingAnimation=0;
        float healthBase=100;

        sf::Clock clock;                        //Timer
        sf::Clock clockReload;

        std::vector<Enemy *> enemies;
        std::vector<Bullet *> bullets;
        std::vector<Tower *> towers;
        Bullet b1;

        sf::Texture mapTexture;
        sf::Sprite map;
};

#endif // MAINWINDOW_H

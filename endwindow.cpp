#include "EndWindow.h"
#include "player.h"
#include <sstream>

EndWindow::EndWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Restart",sf::VideoMode::getDesktopMode().width/1.6,sf::VideoMode::getDesktopMode().height/1.2));
    menus.push_back(new Menu("Quit",sf::VideoMode::getDesktopMode().width/(8/3),sf::VideoMode::getDesktopMode().height/1.2));


    menus.push_back(new Menu("Game over !",sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/6));
    menus.push_back(new Menu("",sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2));
    menus.push_back(new Menu("",sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/3));

    menus.at(1)->changerColor(sf::Color::White);
}

EndWindow::~EndWindow(){
}




void EndWindow::drawElements(){
    std::stringstream ss;

    ss<<"Score : "<<Player::getInstance()->getMoney()<<" $";
    menus.at(3)->changerText(ss.str());

    ss.str("");

    if(Player::getInstance()->getFinalWave()==1){
        ss<<"You have survived "<<Player::getInstance()->getFinalWave()<<" round";
    }
    else {
        ss<<"You have survived "<<Player::getInstance()->getFinalWave()<<" rounds";
    }
    menus.at(4)->changerText(ss.str());



    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int EndWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Q){
        compteur--;
        if(compteur<0){
            compteur = 1;
        }

        for(int i=0;i<menus.size();i++){
            if(i != compteur){
                this->menus.at(i)->changerColor(sf::Color::Red);
            }
            else {
               this->menus.at(i)->changerColor(sf::Color::White);
            }
        }
        return 4;
    }

    if(e.key.code == sf::Keyboard::D){
        compteur++;
        if(compteur>1){
            compteur = 0;
        }

        for(int i=0;i<menus.size();i++){
            if(i != compteur){
               this->menus.at(i)->changerColor(sf::Color::Red);
            }
            else {
               this->menus.at(i)->changerColor(sf::Color::White);
            }
        }
        return 4;
    }

    if(e.key.code == sf::Keyboard::Return){
        switch (compteur) {
            case 0:
                return 5;                           //Restart
            break;

            case 1:
                return 6;                           //Retour au menu principal
            break;
        }
    }
    return 4;
}

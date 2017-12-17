#include "EndWindow.h"
#include "player.h"
#include <sstream>

//********************************************************************************//

EndWindow::EndWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Quit",680,720/1.2));
    menus.push_back(new Menu("Restart",400,720/1.2));

    menus.push_back(new Menu("Game over !",1080/2,720/6));
    menus.push_back(new Menu("",1080/2,720/2));
    menus.push_back(new Menu("",1080/2,720/3));

    menus.at(0)->changerColor(sf::Color::White);
}

EndWindow::EndWindow(const EndWindow &window):Containeur(window){
    for(int i=0; i<menus.size();i++){
        menus.push_back(new Menu(*window.menus.at(i)));
    }
}

EndWindow::~EndWindow(){
    for(int i=0;i<menus.size();i++){
        delete menus.at(i);
        menus.at(i)=0;
    }
    menus.clear();
}

EndWindow& EndWindow::operator=(const EndWindow& window){
    if(this!=&window){
        Containeur::operator=(window);
        for(int i=0; i<menus.size();i++){
            menus.push_back(new Menu(*window.menus.at(i)));
        }
    }
    return *this;
}

//********************************************************************************//

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
                return 7;                           //Restart
            break;

            case 1:
                return 6;                           //Retour au menu principal
            break;
        }
    }
    return 4;
}

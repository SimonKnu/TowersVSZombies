#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Start",1080/2,720/6));
    this->menus.at(0)->changerColor(sf::Color::White);

    menus.push_back(new Menu("Tutorial",1080/2,720/2.5));
    menus.push_back(new Menu("About TowersVSZombies",1080/2,720/2));
    menus.push_back(new Menu("Exit",1080/2,720/1.2));

}

MenuWindow::MenuWindow(const MenuWindow &window):Containeur(window){
    for(int i=0; i<menus.size();i++){
        menus.push_back(new Menu(*window.menus.at(i)));
    }
}

MenuWindow::~MenuWindow(){
    for(int i=0;i<menus.size();i++){
        delete menus.at(i);
        menus.at(i)=0;
    }
    menus.clear();
}

MenuWindow& MenuWindow::operator=(const MenuWindow& window){
    if(this!=&window){
        for(int i=0; i<menus.size();i++){
            menus.push_back(new Menu(*window.menus.at(i)));
        }
    }
    return *this;
}

//********************************************************************************//

void MenuWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int MenuWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Z){
        compteur--;
        if(compteur<0){
            compteur = 3;
        }

        for(int i=0;i<menus.size();i++){
            if(i != compteur){
                this->menus.at(i)->changerColor(sf::Color::Red);
            }
            else {
               this->menus.at(i)->changerColor(sf::Color::White);
            }
        }
        return 0;
    }

    if(e.key.code == sf::Keyboard::S){
        compteur++;
        if(compteur>3){
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
        return 0;
    }

    if(e.key.code == sf::Keyboard::Return){
        switch (compteur) {
            case 0:
                return 1;                           //Lancer le jeu
            break;

            case 1:
                return 5;                           //Lancer le "about"
            break;

            case 2:
                return 2;                           //Lancer le "tutorial"
            break;

            case 3:
                Containeur::getWindow()->close();   //Fermer totalement le programmme
            break;
        }
    }
    return 0;
}

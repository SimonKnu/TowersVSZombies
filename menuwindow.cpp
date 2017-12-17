#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Start",1080/2,720/6));
    this->menus.at(0)->changerColor(sf::Color::White);

    menus.push_back(new Menu("About TowersVSZombies",1080/2,720/2));
    menus.push_back(new Menu("Exit",1080/2,720/1.2));

}

MenuWindow::~MenuWindow(){

}

void MenuWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int MenuWindow::chosenMenu(sf::Event e){
        if(e.key.code == sf::Keyboard::Z){
            compteur--;
            if(compteur<0){
                compteur = 2;
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
            if(compteur>2){
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
                    return 2;                           //Lancer le "about"
                break;

                case 2:
                    Containeur::getWindow()->close();   //Fermer totalement le programmme
                break;
            }
        }
        return 0;

}

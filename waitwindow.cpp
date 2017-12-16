#include "waitwindow.h"

WaitWindow::WaitWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Continue",400,200));

    menus.push_back(new Menu("Give up",400,400));
    menus.at(0)->changerColor(sf::Color::White);
}

WaitWindow::~WaitWindow(){

}




void WaitWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int WaitWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Z){
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
        return 3;
    }

    if(e.key.code == sf::Keyboard::S){
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
        return 3;
    }

    if(e.key.code == sf::Keyboard::Return){
        switch (compteur) {
            case 0:
                return 1;                           //Retour au jeu
            break;

            case 1:
                return 6;                           //Retour au menu principal
            break;
        }
    }

    if(e.key.code == sf::Keyboard::Escape){
        return 1;
    }


    return 3;                                       //Permet de rester sur la fenetre en cours si aucune correspondance
}

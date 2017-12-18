#include "waitwindow.h"

//********************************************************************************//

WaitWindow::WaitWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Continue",540,240));

    menus.push_back(new Menu("Give up",540,480));
    menus.at(0)->changerColor(sf::Color::White);
}

WaitWindow::WaitWindow(const WaitWindow &window):Containeur(window){
    for(int i=0; i<menus.size();i++){
        menus.push_back(new Menu(*window.menus.at(i)));
    }
}

WaitWindow::~WaitWindow(){
    for(int i=0;i<menus.size();i++){
        delete menus.at(i);
        menus.at(i)=0;
    }
    menus.clear();
}

WaitWindow& WaitWindow::operator=(const WaitWindow& window){
    if(this!=&window){
        Containeur::operator=(window);
        for(int i=0; i<menus.size();i++){
            menus.push_back(new Menu(*window.menus.at(i)));
        }
    }
    return *this;
}

//********************************************************************************//

void WaitWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());      //On traite et affiche les éléments de la fenêtre
    }
}

int WaitWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Z){
        //Permet de pouvoir défiler les menus et de se positioner sur le bon élèment grâce au clavier
        compteur--;
        if(compteur<0){
            compteur = 1;
        }

        //On change la couleur en fonction de l'indice qui est sélectionné
        for(int i=0;i<menus.size();i++){
            if(i != compteur){
                this->menus.at(i)->changerColor(sf::Color::Red);
            }
            else {
               this->menus.at(i)->changerColor(sf::Color::White);
            }
        }
        return 3;                                   //On reste sur cette page
    }

    if(e.key.code == sf::Keyboard::S){
        //Permet de pouvoir défiler les menus et de se positioner sur le bon élèment grâce au clavier
        compteur++;
        if(compteur>1){
            compteur = 0;
        }

        //On change la couleur en fonction de l'indice qui est sélectionné
        for(int i=0;i<menus.size();i++){
            if(i != compteur){
               this->menus.at(i)->changerColor(sf::Color::Red);
            }
            else {
               this->menus.at(i)->changerColor(sf::Color::White);
            }
        }
        return 3;                                   //On reste sur cette page
    }

    if(e.key.code == sf::Keyboard::Return){
        switch (compteur) {
            case 0:
                return 1;                           //On retourne sur le jeu
            break;

            case 1:
                return 7;                           //On retourne au menu principal
            break;
        }
    }

    if(e.key.code == sf::Keyboard::Escape){
        return 1;                                   //On retourne sur le jeu
    }


    return 3;                                       //On reste sur cette page tant qu'il ne se passe rien
}

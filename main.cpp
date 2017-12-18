#include <SFML/Graphics.hpp>
#include "menuwindow.h"
#include "endwindow.h"
#include "aboutwindow.h"
#include "containeur.h"
#include "waitwindow.h"
#include "mainwindow.h"
#include "tutowindow.h"
#include "iostream"
#include <vector>

int main(){

    //Creation de la fenetre
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1080,720),"TowersVSZombies");

    //On déclare un compteur qui vont servir à afficher les différentes fenetres
    int countWindow = 0;

    //Variable "tampon"
    int newWindow;

    //Liste contenant un attribut de type window
    std::vector<Containeur *> containeur;
    containeur.push_back(new MenuWindow(window));           //countWindow = 0 -> Affichage MenuWindow
    containeur.push_back(new MainWindow(window));           //countWindow = 1 -> Affichage MainWindow
    containeur.push_back(new AboutWindow(window));          //countWindow = 2 -> Affichage AboutWindow
    containeur.push_back(new WaitWindow(window));           //countWindow = 3 -> Affichage WaitWindow
    containeur.push_back(new EndWindow(window));            //countWindow = 4 -> Affichage EndWindow
    containeur.push_back(new TutoWindow(window));           //countWindow = 5 -> Affichage TutoWindow

    while(window->isOpen()){
        sf::Event e;


        while(window->pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window->close();
            }
            if(e.type==sf::Event::KeyReleased){
                //Permet de récupérer a chaque fois le bon élèment en fonction des interactions de l'utilisateur
                newWindow = containeur.at(countWindow)->chosenMenu(e);

                //Petit test permettant de savoir si, à la fin d'une partie, le joueur veut restart ou quitter
                //Dans les deux cas, il faut remplacer la fenêtre jeu pour en avoir une nouvelle et recréer le joueur
                //pour pouvoir rejouer proprement
                if(newWindow==6 || newWindow==7){
                    Player::getInstance()->reset();
                    containeur.at(1)=new MainWindow(window);

                    if(newWindow==6){
                        countWindow = 1;            //Permet de restart directement
                    }
                    else {
                        countWindow = 0;            //Permet de revenir au menu principal
                    }
                }
                else {
                    countWindow = newWindow;
               }
            }
        }

        //On vérifie que le joueur est toujours en vie. Sinon, on force la fin de la partie
        if(Player::getInstance()->getHealth()<=0){
            countWindow = 4;
        }

        //Permet d'afficher les élèments pour chaque fenêtre grace au compteur;
        window->clear();
        containeur.at(countWindow)->drawElements();
        window->display();
    }

    return 0;
}




#include <SFML/Graphics.hpp>
#include "menuwindow.h"
#include "endwindow.h"
#include "aboutwindow.h"
#include "containeur.h"
#include "waitwindow.h"
#include "mainwindow.h"
#include "iostream"
#include <vector>

int main(){

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2),"TowersVSZombies");
    int countWindow = 0;
    int newWindow;

    std::vector<Containeur *> containeur;
    containeur.push_back(new MenuWindow(window));
    containeur.push_back(new MainWindow(window));
    containeur.push_back(new AboutWindow(window));
    containeur.push_back(new WaitWindow(window));
    containeur.push_back(new EndWindow(window));

    while(window->isOpen()){
        sf::Event e;


        while(window->pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window->close();
            }
            if(e.type==sf::Event::KeyReleased){
                newWindow = containeur.at(countWindow)->chosenMenu(e);
                if(newWindow==5 || newWindow==6){
                    Player::getInstance()->reset();
                    containeur.at(1)=new MainWindow(window);

                    if(newWindow==5){
                        countWindow = 1;
                    }
                    else {
                        countWindow = 0;
                    }
                }
                else {
                    countWindow = newWindow;
               }
            }
        }

        if(Player::getInstance()->getHealth()<=0){
            countWindow = 4;
        }


        window->clear();
        containeur.at(countWindow)->drawElements();
        window->display();
    }

    return 0;
}




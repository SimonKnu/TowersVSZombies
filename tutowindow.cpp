#include "tutowindow.h"

//********************************************************************************//

TutoWindow::TutoWindow(sf::RenderWindow *containeur):Containeur(containeur)
{
    menus.push_back(new Menu("Tutorial",1080/2, 720/6));
    menus.push_back(new Menu("Move forward   :\tZ\n"
                             "Move backward  :\tS\n"
                             "Move left       :\tQ\n"
                             "Move right      :\tD\n\n"
                             "Put a turrel    :\tA\n\n"
                             "Shoot           :\tLeft mouse click\n"
                             "Reload          :\tR",1080/3, 720/2));

    menus.push_back(new Menu("Back",1080/2, 720/1.2));
    menus.at(2)->changerColor(sf::Color::White);
}

TutoWindow::TutoWindow(const TutoWindow &window):Containeur(window){
    for(int i=0; i<menus.size();i++){
        menus.push_back(new Menu(*window.menus.at(i)));
    }
}

TutoWindow::~TutoWindow(){
    for(int i=0;i<menus.size();i++){
        delete menus.at(i);
        menus.at(i)=0;
    }
    menus.clear();
}


TutoWindow& TutoWindow::operator=(const TutoWindow& window){
    if(this!=&window){
        Containeur::operator=(window);
        for(int i=0; i<menus.size();i++){
            menus.push_back(new Menu(*window.menus.at(i)));
        }
    }
    return *this;
}

//********************************************************************************//

void TutoWindow::drawElements(){
    for(int i=0;i<menus.size();i++){
        Containeur::getWindow()->draw(menus.at(i)->getText());
    }
}

int TutoWindow::chosenMenu(sf::Event e){
    if(e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Escape){
        return 0;
    }
    return 5;
}

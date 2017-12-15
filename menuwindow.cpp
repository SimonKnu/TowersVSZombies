#include "MenuWindow.h"
#include <SFML/Graphics.hpp>


MenuWindow::MenuWindow()
{
    menus.push_back(new Menu("Start",400,100));
    menus.push_back(new Menu("About",400,300));
    menus.push_back(new Menu("Quit",400,500));

}

MenuWindow::~MenuWindow(){

}

void MenuWindow::dessiner(sf::RenderWindow *window){
  /*  for(int i=0;i<menus.size();i++){
        window->draw(menus.at(i));
    }*/
}


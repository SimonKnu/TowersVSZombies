#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include "SFML/Graphics.hpp"

class EndWindow
{
    private :

    public:
        EndWindow();
        ~EndWindow();

        void dessiner(sf::RenderWindow *window);
};

#endif // ENDWINDOW_H

#include "sound.h"

Sound* Sound::instance = 0;

//********************************************************************************//

Sound::Sound(){

}

Sound::~Sound(){
    delete instance;
    instance=0;
}

Sound* Sound::getInstance(){
    if(instance==0){
        instance = new Sound();
    }
    return instance;
}

//********************************************************************************//

//Permet d'ajouter le fichier audio gràce au buffer. Ce buffer sera ajouté dans une liste
void Sound::addFile(std::string txt){
    sf::SoundBuffer buffer;
    sf::Sound sound;

    if (!buffer.loadFromFile(txt))
    {
        // Erreur...
    }

    buffers.push_back(buffer);
    sounds.push_back(sound);
}

+//Permet d'ajouter le buffer sur le l'objet sound et de démarrer la son
void Sound::play(int index){
    sounds.at(index).setBuffer(buffers.at(index));
    sounds.at(index).play();
}

void Sound::loop(int ind){
    sounds.at(ind).setLoop(true);
}

void Sound::pause(int ind){
    sounds.at(ind).pause();
}

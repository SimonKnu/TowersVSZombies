#include "sound.h"

Sound* Sound::instance = 0;

Sound::Sound(){

}

Sound* Sound::getInstance(){
    if(instance==0){
        instance = new Sound();
    }
    return instance;
}

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

void Sound::play(int index){
    sounds.at(index).setBuffer(buffers.at(index));
    sounds.at(index).play();
}


#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <SFML/Audio.hpp>
#include <string>

class Sound
{
    private:

        std::vector< sf::SoundBuffer> buffers;
        std::vector< sf::Sound> sounds;

        static Sound* instance;
        Sound();

    public:
        static Sound* getInstance();

        void addFile(std::string txt);
        void play(int index);
};

#endif // SOUND_H

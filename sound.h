#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <SFML/Audio.hpp>
#include <string>

class Sound
{
    private:
        std::vector<sf::SoundBuffer> buffers;
        std::vector<sf::Sound> sounds;

        static Sound* instance;
        Sound();

    public:
        ~Sound();
        static Sound* getInstance();

        void addFile(std::string txt);
        void play(int index);
        void loop(int play);
        void pause(int ind);
};

#endif // SOUND_H

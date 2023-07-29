
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class AudioControl{

private:
    sf::SoundBuffer buffers[100];
    int index=0;
    
public:
    std::map<std::string, sf::SoundBuffer*>  snd_files;  	
    void load_sndfile(std::string name, std::string path);
	
	void play_sound
};

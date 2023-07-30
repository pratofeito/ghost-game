#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include <cstdlib>

class AudioControl{
    
public:
	int fading_in;
	float volume;
	float fade_time;
	float curr_time;
	sf::Music* current = 0;
    std::map<std::string, sf::Music*> mm;
    void load_music(std::string name, std::string path);
    void update_music(float dt);
    void fade_in(std::string name, float time);
    void fade_out(std::string name, float time);
    void play(std::string name);
};


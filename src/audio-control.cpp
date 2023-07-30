
#include "audio-control.hpp"


void AudioControl::load_music(std::string name, std::string path){

	sf::Music* m = new sf::Music;
    if(!m->openFromFile(path)){
        std::cout << "error loading audio file " << path << "\n";
        delete m;
        std::exit(1);
    }
    
    mm[name] = m;
}

void AudioControl::play(std::string name){
    if(current){
        current->stop();
    }
	if(mm.find(name)==mm.end()){
	    std::cout << "play: no music named " << name << "\n";
	    std::exit(1);
	}
    current = mm[name];
    mm[name]->play();
}

void AudioControl::fade_in(std::string name, float time){
    if(current){
        current->stop();
    }
    if(mm.find(name)==mm.end()){
        std::cout << "fade_in: no music named " << name << "\n";
        std::exit(1);
    }
    fade_time = time;
    curr_time = 0.0f;
    current = mm[name];
    fading_in = 1;
    mm[name]->setRelativeToListener(true);
    mm[name]->setVolume(0.0f);
    mm[name]->play();
}

void AudioControl::fade_out(std::string name, float time){
    if(current){
        current->stop();
    }
    if(mm.find(name)==mm.end()){
        std::cout << "fade_out: no music named " << name << "\n";
        std::exit(1);
    }
    fade_time = time;
    curr_time = 0.0f;
    current = mm[name];
    fading_in = -1;
    mm[name]->setRelativeToListener(true);
    mm[name]->setVolume(0.0f);
    mm[name]->play();
}

void AudioControl::update_music(float dt){
	curr_time += dt;
	if(fading_in==1){
		if(curr_time>=fade_time){
			fading_in = 0;
			current->setVolume(100.0f);
			return;
		}
		current->setVolume(100.0f*curr_time/fade_time);
	}
	if(fading_in == -1){
		if(curr_time>=fade_time){
			fading_in = 0;
			current->setVolume(0.0f);
			return;
		}
		current->setVolume(100.0f-100.0f*curr_time/fade_time);
	}
}

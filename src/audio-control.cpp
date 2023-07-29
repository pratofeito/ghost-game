
#include "audio-control.hpp"



void load_sndfile(std::string name, std::string path)
{
    if(!buffers[index].loadFromFile(path)){
        std::cout << "failed to load sound file\"" << path << "\"\n;
        return;
    }
    snd_files[name] = &buffers[index]; 
    index++; 
}




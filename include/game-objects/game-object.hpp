#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    bool collidable;
    std::string type;
};

#endif
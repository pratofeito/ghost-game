#include "game-objects/wall.hpp"

Wall::Wall()
{
    collidable = true;
    type = "wall";
}

void Wall::log()
{
    std::cout << "this is a wall" << std::endl;
}
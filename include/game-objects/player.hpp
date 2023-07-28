#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "game-objects/game-object.hpp"

enum Direction
{
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

class Player : public GameObject
{
private:
public:
    Direction facing;
    sf::Vector2i grid_position;
    sf::RectangleShape hitbox;

    Player();
};

#endif
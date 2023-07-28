#include "game-objects/player.hpp"

Player::Player ()
{
    collidable = true;
    type = "player";

    facing = FRONT;
    grid_position = sf::Vector2i(0, 0);
}
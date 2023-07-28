#include "game-objects/npc.hpp"

Npc::Npc()
{
    collidable = true;
    type = "npc";

    grid_position = sf::Vector2i(0, 0);
}

std::string Npc::get_sentence()
{
    return "sou um npc!";
}

void set_answer(int answer)
{
    return;
}
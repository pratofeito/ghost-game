#ifndef NPC_HPP
#define NPC_HPP

#include "game-objects/game-object.hpp"

class Npc : public GameObject
{
private:
public:
    sf::Vector2i grid_position;
    sf::RectangleShape hitbox;

    Npc();

    std::string get_sentence();
    void set_answer(int answer);
};

#endif
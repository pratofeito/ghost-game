#ifndef NPC_HPP
#define NPC_HPP

#include "game-objects/game-object.hpp"
#include "dialogue.hpp"
#include <cstdlib>


class Npc : public GameObject
{
private:
public:
    sf::Vector2i grid_position;
    sf::RectangleShape hitbox;
	
    Npc();

    Dialogue dialogue;
    void dialogue_assert_initialized();
    std::string get_sentence();
    std::string get_answer(int);
    int get_number_of_answers();
    void set_answer(int answer);
    void reset_dialogue();
};

#endif

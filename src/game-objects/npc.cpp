#include "game-objects/npc.hpp"

Npc::Npc()
{
    collidable = true;
    type = "npc";

    grid_position = sf::Vector2i(0, 0);
}

void Npc::dialogue_assert_initialized()
{
    if(!dialogue.initialized)
    {
        std::cout << "dialogue uninitialized!\n";
        std::exit(1);
    }
}

std::string Npc::get_sentence()
{
    dialogue_assert_initialized();
    return *(dialogue.get_current());
}

int Npc::get_number_of_answers()
{    
	dialogue_assert_initialized();
	return dialogue.get_number_of_answers();
}

std::string Npc::get_answer(int answer)
{
    dialogue_assert_initialized();
	return *(dialogue.get_answer(answer));
}

void Npc::set_answer(int answer)
{
    dialogue_assert_initialized();  
    dialogue.set_answer(answer);
    return;
}

void Npc::reset_dialogue(){
	dialogue.curr_id = 1;
}



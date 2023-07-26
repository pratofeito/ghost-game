/**
 * @file game-state.hpp
 * @date 2023-01-06
 * 
 * @brief Example game state. Runs a bouncing ball demo.
 * 
 */

#ifndef PTE_GAME_STATE_HPP
#define PTE_GAME_STATE_HPP

#include <cstdio>
#include <cmath>
#include <prato-engine/generic-state.hpp>
#include "states/pause-state.hpp"
#include "definitions.hpp"



class GameState : public pte::GenericState
{
private:
    sf::Sprite pause_button;

    // view
    sf::View default_view;
    sf::View view;

    // player
    sf::Vector2f center;
    sf::RectangleShape player;

    // movement
	float t_antes=0, t_agora=0;

    // map
    int map[10000];
    int line=0, column=0;
    sf::Sprite tiles[NO_TILES];

public:
    using GenericState::GenericState;

    void init();
    void handle_input();
    void update(float delta_time);
    void draw(float delta_time);
    
    // tiling methods
    void read_csv();
    sf::Vector2f tile_position(int i, int j);
    
};

#endif

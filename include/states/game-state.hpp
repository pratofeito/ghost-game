/**
 * @file game-state.hpp
 * @date 2023-01-06
 * 
 * @brief main game state
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

    // input stack
    std::vector<int> key_stack;
    void push_stack(int input);
    void del_stack(int input);
    int update_control();

    // view
    sf::View default_view;
    sf::View view;

    // player
    sf::RectangleShape player;

    // movement
    bool moving;
    float moving_elapsed_time;

    
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
    
    // movement methods
    void move_adjacent_tile(int x, int y);
    sf::Vector2i update_movement(float delta_time);
};

#endif

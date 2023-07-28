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
#include <fstream>
#include <sstream>
#include <prato-engine/generic-state.hpp>
#include "states/pause-state.hpp"
#include "gui.hpp"
#include "definitions.hpp"

#include "game-objects/game-object.hpp"
#include "game-objects/wall.hpp"

#define INTERVAL 0.01
#define SIZE 20

class GameState : public pte::GenericState
{
private:
    InputManager input;

    sf::Sprite pause_button;

    // input stack
    std::vector<int> key_stack;
    void push_stack(int input);
    void del_stack(int input);
    int update_control();

    // view
    sf::View default_view;
    sf::View view;
    float time_interval;

    // player
    sf::RectangleShape player;
    sf::Vector2i player_pos;
    sf::Vector2i new_player_pos;

    // movement
    bool moving;
    float moving_elapsed_time;
    sf::Vector2f pos_start;
    sf::Vector2f pos_end;
    sf::Vector2f center;

    // map
    int map[10000];
    int line = 0, column = 0;
    sf::Sprite tiles[NO_TILES];

    // game objects
    // std::vector<std::vector<GameObject *>> game_objects(5)(5);

    std::vector<std::vector<GameObject *>> game_objects;

    // std::vector<std::vector<int>> fog(SIZE, std::vector<int>(SIZE));

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
    sf::Vector2f update_movement(float delta_time);

    // game objects
    void init_walls();
};

#endif

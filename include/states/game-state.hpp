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
#include <prato-engine/generic-state.hpp>
#include "states/pause-state.hpp"
#include "gui.hpp"
#include "definitions.hpp"
#include "dialogue.hpp"

#include "game-objects/game-object.hpp"
#include "game-objects/wall.hpp"
#include "game-objects/player.hpp"
#include "game-objects/npc.hpp"
#include "dialog-box.hpp"

#define INTERVAL 0.01
#define SIZE 20

class GameState : public pte::GenericState
{
private:
    InputManager input;

    sf::Sprite pause_button;
    Config config_defs;

    // input stack
    std::vector<int> key_stack;
    void push_stack(int input);
    void del_stack(int input);
    int update_control();

    // view
    sf::View default_view;
    sf::View view;
    float time_interval;

    // entities
    Player player;
    Npc npc1;

    // dialog
    DialogBox *dialog_box;

    // movement
    bool moving;
    float moving_elapsed_time;
    sf::Vector2f pos_start;
    sf::Vector2f pos_end;
    sf::Vector2f center;

    // map
    int map[10000];
    int coll[10000];
    int line = 0, column = 0;
    sf::Sprite tiles[NO_TILES];

    // debug
#ifdef DEBUG
    sf::Text coord[50][50];
    char coord_s[200];
#endif

    // game objects
    std::vector<std::vector<GameObject *>> game_objects;

public:
    using GenericState::GenericState;

    void init();
    void handle_input();
    void update(float delta_time);
    void draw(float delta_time);

    // tiling methods
    void read_csv(char const *);
    sf::Vector2f tile_position(int i, int j);
    int tile_id(sf::Vector2i tile);

    // movement methods
    void move_adjacent_tile(int x, int y);
    sf::Vector2f update_movement(float delta_time);

    // interaction
    Npc *npc_talking;
    float click_interval_answer = 0;
    bool text_writing;
    int phrase_max_string = 0;
    // std::string top_box_string;
    void interact(Npc &npc);
    void update_interaction(float delta_time);

    // game objects
    void init_walls();
};

#endif

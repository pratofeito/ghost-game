/**
 * @file menu-state.hpp
 * @date 2023-01-06
 *
 * @brief Example game menu state.
 *
 */

#ifndef PTE_MENU_STATE_HPP
#define PTE_MENU_STATE_HPP

#include <prato-engine/generic-state.hpp>
#include "states/game-state.hpp"
#include "config-handler.hpp"
#include "definitions.hpp"

#include "button.hpp"

#define CLICK_DELAY 0.3

class MainMenuState : public pte::GenericState
{
private:
    Config config_defs;
    InputManager input;

    Button *play_button;
    Button *credits_button;
    Button *exit_button;

    Checkbox *checkbox_1x;
    Checkbox *checkbox_2x;

    sf::Text label_checkbox;
    sf::Text title;

    float time_since_last_click;

public:
    using GenericState::GenericState;

    void init();
    void handle_input();
    void update(float delta_time);
    void draw(float delta_time);
};

#endif
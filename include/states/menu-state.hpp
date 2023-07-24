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

class MainMenuState : public pte::GenericState
{
private:
    Config config_defs;
    InputManager input;

    sf::Sprite play_button;
    sf::Sprite quit_button;
    sf::Text title;

public:
    using GenericState::GenericState;

    void init();
    void handle_input();
    void update(float delta_time);
    void draw(float delta_time);
};

#endif
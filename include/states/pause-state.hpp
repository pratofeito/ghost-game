/**
 * @file pause-state.hpp
 * @date 2023-01-06
 *
 * @brief Example pause state
 *
 */

#ifndef PTE_PAUSE_STATE_HPP
#define PTE_PAUSE_STATE_HPP

#include <prato-engine/generic-state.hpp>
#include "states/menu-state.hpp"
#include "config-handler.hpp"
#include "definitions.hpp"

class PauseState : public pte::GenericState
{
private:
    Config config_defs;

    sf::Sprite resume_button;
    sf::Sprite home_button;
    sf::Text title;

public:
    using GenericState::GenericState;

    void init();
    void handle_input();
    void update(float delta_time);
    void draw(float delta_time);
};

#endif
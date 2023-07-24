#ifndef PTE_BUTTON_HPP
#define PTE_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "config-handler.hpp"

class InputManager
{
private:
    Config config_defs;
public:
    InputManager();
    bool is_sprite_clicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
};

#endif
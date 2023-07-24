#include "button.hpp"

InputManager::InputManager()
{
    // load configs;
    config_defs.load("data/config.txt");
}
bool InputManager::is_sprite_clicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
{
    int scale = stoi(config_defs.get("SCREEN_SCALE"));

    if (sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect temp_rect(object.getPosition().x * scale, object.getPosition().y * scale, object.getGlobalBounds().width * scale, object.getGlobalBounds().height * scale);

            if (temp_rect.contains(sf::Mouse::getPosition(window)))
            {
                return true;
            }
        }

        return false;
}
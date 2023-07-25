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

// -------------------------------------- button --------------------------------------

Button::Button(sf::RenderWindow &window)
{
    this->window = &window;
    sprite.setPosition(0, 0);
    set_size(100, 100);
}

void Button::set_texture(std::string texture_path)
{
    texture.loadFromFile(texture_path);
    sprite.setTexture(texture);

    hover_texture = texture;
    pressed_texture = texture;

    sf::Vector2f center;
    center.x = sprite.getGlobalBounds().getSize().x / 2;
    center.y = sprite.getGlobalBounds().getSize().y / 2;
    sprite.setOrigin(center);

    // load screen scale config
    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));
}

void Button::set_size(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Button::set_hover_texture(std::string texture_path)
{
    hover_texture.loadFromFile(texture_path);
}

void Button::set_pressed_texture(std::string texture_path)
{
    pressed_texture.loadFromFile(texture_path);
}

void Button::set_position(int pos_x, int pos_y)
{
    x = pos_x;
    y = pos_y;
    sprite.setPosition(x, y);
}

void Button::update()
{
    // verify mouse hover
    sf::IntRect temp_rect((x - width / 2) * screen_scale, (y - height / 2) * screen_scale, width * screen_scale, height * screen_scale);
    if (temp_rect.contains(sf::Mouse::getPosition(*window)))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sprite.setTexture(pressed_texture);
        }
        else
        {
            sprite.setTexture(hover_texture);
        }
    }
    else
    {
        sprite.setTexture(texture);
    }
}

void Button::set_text(std::string text_string, sf::Font &font, int character_size, sf::Uint32 style, sf::Color color)
{
    font.setSmooth(false);
    this->text_string = text_string;

    text.setFont(font);
    text.setString(text_string);
    text.setCharacterSize(character_size);
    text.setStyle(style);
    text.setFillColor(color);
    
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(x, y);
}

void Button::draw()
{
    window->draw(sprite);
    window->draw(text);
}

// ------------------------------------- checkbox -------------------------------------

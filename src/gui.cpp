#include "gui.hpp"

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
    visible = true;
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
    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));

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
    if (!visible)
    {
        return;
    }

    window->draw(sprite);
    window->draw(text);
}

bool Button::is_pressed()
{
    if (!visible)
    {
        return false;
    }

    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));

    sf::IntRect temp_rect((x - width / 2) * screen_scale, (y - height / 2) * screen_scale, width * screen_scale, height * screen_scale);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_rect.contains(sf::Mouse::getPosition(*window)))
    {
        return true;
    }

    return false;
}

void Button::set_visible(bool visible)
{
    this->visible = visible;
}

// ------------------------------------- checkbox -------------------------------------

Checkbox::Checkbox(sf::RenderWindow &window)
{
    this->window = &window;
    sprite.setPosition(0, 0);
    set_size(100, 100);
    selected = false;
    since_last_click = 1;
}

void Checkbox::set_size(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Checkbox::set_position(int pos_x, int pos_y)
{
    x = pos_x;
    y = pos_y;
    sprite.setPosition(x, y);
}

void Checkbox::set_text(std::string text_string, sf::Font &font, int character_size, sf::Uint32 style, sf::Color color)
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

void Checkbox::set_texture(std::string texture_path)
{
    texture.loadFromFile(texture_path);
    sprite.setTexture(texture);

    texture = texture;
    selected_texture = texture;

    sf::Vector2f center;
    center.x = sprite.getGlobalBounds().getSize().x / 2;
    center.y = sprite.getGlobalBounds().getSize().y / 2;
    sprite.setOrigin(center);

    // load screen scale config
    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));
}

void Checkbox::set_selected_texture(std::string texture_path)
{
    selected_texture.loadFromFile(texture_path);
}

void Checkbox::update(float delta_time)
{
    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));

    // verify mouse hover
    sf::IntRect temp_rect((x - width / 2) * screen_scale, (y - height / 2) * screen_scale, width * screen_scale, height * screen_scale);

    since_last_click += delta_time;

    // if (since_last_click >= MIN_DELAY && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_rect.contains(sf::Mouse::getPosition(*window)))
    // {
    //     if (selected)
    //     {
    //         selected = false;
    //     }
    //     else
    //     {
    //         selected = true;
    //     }

    //     since_last_click = 0;
    // }

    if (selected)
    {
        sprite.setTexture(selected_texture);
    }
    else
    {
        sprite.setTexture(texture);
    }
}

void Checkbox::draw()
{
    window->draw(sprite);
    window->draw(text);
}

bool Checkbox::is_pressed()
{
    config_defs.load("data/config.txt");
    screen_scale = stoi(config_defs.get("SCREEN_SCALE"));

    sf::IntRect temp_rect((x - width / 2) * screen_scale, (y - height / 2) * screen_scale, width * screen_scale, height * screen_scale);

    if (since_last_click >= MIN_DELAY && sf::Mouse::isButtonPressed(sf::Mouse::Left) && temp_rect.contains(sf::Mouse::getPosition(*window)))
    {
        since_last_click = 0;
        return true;
    }

    return false;
}
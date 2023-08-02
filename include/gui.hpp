#ifndef PTE_BUTTON_HPP
#define PTE_BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "config-handler.hpp"

#define MIN_DELAY 1

class InputManager
{
private:
    Config config_defs;

public:
    InputManager();
    bool is_sprite_clicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
};

class Button
{
private:
    sf::RenderWindow *window;
    Config config_defs;
    int screen_scale;
    sf::Sprite sprite;

    int x, y;
    int width, height;

    sf::Texture texture;
    sf::Texture hover_texture;
    sf::Texture pressed_texture;

    bool visible;

    std::string text_string;
    sf::Font *font;

public:
    sf::Text text;
    Button(sf::RenderWindow &window);

    void set_size(int width, int height);
    void set_position(int pos_x, int pos_y);
    void set_text(std::string text_string, sf::Font &font, int character_size, sf::Uint32 style, sf::Color color);

    void set_texture(std::string texture_path);
    void set_hover_texture(std::string texture_path);
    void set_pressed_texture(std::string texture_path);
    void set_visible(bool visible);

    void update();
    void draw();

    bool is_pressed();
};

class Checkbox
{
private:
    sf::RenderWindow *window;
    Config config_defs;
    int screen_scale;
    sf::Sprite sprite;

    int x, y;
    int width, height;
    float since_last_click;

    sf::Texture texture;
    sf::Texture selected_texture;

    sf::Text text;
    std::string text_string;
    sf::Font *font;

public:
    bool selected;

    Checkbox(sf::RenderWindow &window);

    void set_size(int width, int height);
    void set_position(int pos_x, int pos_y);
    void set_text(std::string text_string, sf::Font &font, int character_size, sf::Uint32 style, sf::Color color);

    void set_texture(std::string texture_path);
    void set_selected_texture(std::string texture_path);

    void update(float delta_time);
    void draw();

    bool is_pressed();
};

#endif
#ifndef DIALOG_BOX_HPP
#define DIALOG_BOX_HPP

#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "gui.hpp"

class DialogBox
{
private:
    sf::RenderWindow *window;
    // sf::Texture top_box_texture;
    // sf::Texture option_texture;
    // sf::Texture option_hover_texture;
    // sf::Texture option_pressed_texture;

    // sf::Sprite top_box;
    // sf::Sprite option_1;
    // sf::Sprite option_2;
    // sf::Sprite option_3;

    Button *top_box;
    Button *option_1;
    Button *option_2;
    Button *option_3;

public:
    bool active;

    DialogBox(sf::RenderWindow *window);

    void update(float delta_time);
    void draw();
};

#endif
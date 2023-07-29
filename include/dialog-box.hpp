#ifndef DIALOG_BOX_HPP
#define DIALOG_BOX_HPP

#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "gui.hpp"

class DialogBox
{
private:
    sf::RenderWindow *window;

public:
    bool active;
    Button *top_box;
    Button *option_1;
    Button *option_2;
    Button *option_3;
    Button *exit;

    sf::Texture background_texture;
    sf::Sprite background;

    DialogBox(sf::RenderWindow *window);

    void update(float delta_time);
    void draw();
};

#endif
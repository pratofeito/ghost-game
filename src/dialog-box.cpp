#include "dialog-box.hpp"

DialogBox::DialogBox(sf::RenderWindow *window)
{
    active = false;
    this->window = window;

    // init top box
    top_box = new Button(*window);
    top_box->set_size(468, 96);
    top_box->set_texture(TOP_BOX_TEXTURE_PATH);
    top_box->set_position(SCREEN_WIDTH / 2, 15 + 96 / 2);

    // options background
    background_texture.loadFromFile(BACKGROUNG_TEXTURE_PATH);
    background.setTexture(background_texture);
    background.setOrigin(sf::Vector2f(background_texture.getSize().x / 2, background_texture.getSize().y / 2));
    background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (51 + 12));

    // option 1
    option_1 = new Button(*window);
    option_1->set_size(468, 34);
    option_1->set_texture(OPTION_TEXTURE_PATH);
    option_1->set_hover_texture(OPTION_HOVER_TEXTURE_PATH);
    option_1->set_pressed_texture(OPTION_PRESSED_TEXTURE_PATH);
    option_1->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (34 / 2 + 2 * 34 + 15) + 2 * 3);

    // option 2
    option_2 = new Button(*window);
    option_2->set_size(468, 34);
    option_2->set_texture(OPTION_TEXTURE_PATH);
    option_2->set_hover_texture(OPTION_HOVER_TEXTURE_PATH);
    option_2->set_pressed_texture(OPTION_PRESSED_TEXTURE_PATH);
    option_2->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (34 / 2 + 1 * 34 + 15) + 1 * 3);

    // option 2
    option_3 = new Button(*window);
    option_3->set_size(468, 34);
    option_3->set_texture(OPTION_TEXTURE_PATH);
    option_3->set_hover_texture(OPTION_HOVER_TEXTURE_PATH);
    option_3->set_pressed_texture(OPTION_PRESSED_TEXTURE_PATH);
    option_3->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (34 / 2 + 0 * 34 + 15));

    // exit
    exit = new Button(*window);
    exit->set_size(468, 34);
    exit->set_texture(OPTION_TEXTURE_PATH);
    exit->set_hover_texture(OPTION_HOVER_TEXTURE_PATH);
    exit->set_pressed_texture(OPTION_PRESSED_TEXTURE_PATH);
    exit->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (34 / 2 + 2 * 34 + 15) + 2 * 3);

}

void DialogBox::update(float delta_time)
{
    top_box->update();
    exit->update();
    option_1->update();
    option_2->update();
    option_3->update();
}

void DialogBox::draw()
{
    if (!active)
    {
        return;
    }

    top_box->draw();

    window->draw(background);
    exit->draw();
    option_1->draw();
    option_2->draw();
    option_3->draw();
}
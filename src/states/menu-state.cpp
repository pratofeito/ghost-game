#include "states/menu-state.hpp"

void MainMenuState::init()
{
    // load config
    config_defs.load("data/config.txt");

    // setup title
    assets->load_font("default_font", config_defs.get("DEFAULT_FONT_PATH"));
    this->title.setFont(assets->get_font("default_font"));
    this->title.setString("MAIN MENU");
    this->title.setCharacterSize(55);
    this->title.setFillColor(sf::Color::White);
    this->title.setPosition((SCREEN_WIDTH / 2) - (this->title.getGlobalBounds().width / 2), SCREEN_HEIGHT * 0.2);

    // setup play button
    assets->load_texture("play_button", MAIN_MENU_PLAY_BUTTON);
    this->play_button.setTexture(assets->get_texture("play_button"));
    this->play_button.setPosition((SCREEN_WIDTH / 2) - (this->play_button.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + this->play_button.getGlobalBounds().height);

    // setup quit button
    assets->load_texture("quit_button", MAIN_MENU_QUIT_BUTTON);
    this->quit_button.setTexture(assets->get_texture("quit_button"));
    this->quit_button.setPosition((SCREEN_WIDTH / 2) - (this->quit_button.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + this->quit_button.getGlobalBounds().height * 2.2);

    // load fonts
    assets->load_font("d_font", DEFAULT_FONT);
    assets->get_font("d_font").setSmooth(false);

    // new button
    test_button = new Button(*window);
    test_button->set_size(173, 43);
    test_button->set_texture("resources/main-menu/btn_texture.png");
    test_button->set_hover_texture("resources/main-menu/btn_hover_texture.png");
    test_button->set_pressed_texture("resources/main-menu/btn_pressed_texture.png");
    test_button->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    test_button->set_text("PLAY", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);
}

void MainMenuState::handle_input()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            window->close();
        }

        // if (input.is_sprite_clicked(this->play_button, sf::Mouse::Left, *window))
        // {
        //     // Switch to game state
        //     add_state<GameState>(true);
        // }
    }
}

void MainMenuState::update(float delta_time)
{
    test_button->update();
}

void MainMenuState::draw(float delta_time)
{
    window->clear(sf::Color(65, 11, 95));

    window->draw(this->title);
    // window->draw(this->play_button);
    // window->draw(this->quit_button);

    test_button->draw();

    window->display();
}

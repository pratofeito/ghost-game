#include "states/menu-state.hpp"

void MainMenuState::init()
{
    // load config
    config_defs.load("data/config.txt");

    // load fonts
    assets->load_font("d_font", DEFAULT_FONT);
    assets->get_font("d_font").setSmooth(false);

    // title
    title.setFont(assets->get_font("d_font"));
    title.setCharacterSize(40);
    title.setStyle(sf::Text::Bold);
    title.setString("GHOST GAME");
    title.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - title.getGlobalBounds().width / 2, 80));

    // play button
    play_button = new Button(*window);
    play_button->set_size(173, 43);
    play_button->set_texture("resources/main-menu/btn_texture.png");
    play_button->set_hover_texture("resources/main-menu/btn_hover_texture.png");
    play_button->set_pressed_texture("resources/main-menu/btn_pressed_texture.png");
    play_button->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25);
    play_button->set_text("play", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);

    // credits button
    credits_button = new Button(*window);
    credits_button->set_size(173, 43);
    credits_button->set_texture("resources/main-menu/btn_texture.png");
    credits_button->set_hover_texture("resources/main-menu/btn_hover_texture.png");
    credits_button->set_pressed_texture("resources/main-menu/btn_pressed_texture.png");
    credits_button->set_position(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 43 + 10 - 25);
    credits_button->set_text("credits", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);

    // exit button
    exit_button = new Button(*window);
    exit_button->set_size(173, 43);
    exit_button->set_texture("resources/main-menu/btn_texture.png");
    exit_button->set_hover_texture("resources/main-menu/btn_hover_texture.png");
    exit_button->set_pressed_texture("resources/main-menu/btn_pressed_texture.png");
    exit_button->set_position(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 43 * 2 + 10 * 2 - 25);
    exit_button->set_text("exit", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);

    // checkbox text
    label_checkbox.setFont(assets->get_font("d_font"));
    label_checkbox.setCharacterSize(20);
    label_checkbox.setStyle(sf::Text::Bold);
    label_checkbox.setString("window scale:");
    label_checkbox.setPosition(sf::Vector2f(SCREEN_WIDTH - 215, SCREEN_HEIGHT - 20 - 25));

    // checkbox 1x
    checkbox_1x = new Checkbox(*window);
    checkbox_1x->set_size(30, 30);
    checkbox_1x->set_texture("resources/main-menu/cb_texture.png");
    checkbox_1x->set_selected_texture("resources/main-menu/cb_selected_texture.png");
    checkbox_1x->set_position(SCREEN_WIDTH - 15 - 20 - 40, SCREEN_HEIGHT - 15 - 20);
    checkbox_1x->set_text("1x", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);

    // checkbox 2x
    checkbox_2x = new Checkbox(*window);
    checkbox_2x->set_size(30, 30);
    checkbox_2x->set_texture("resources/main-menu/cb_texture.png");
    checkbox_2x->set_selected_texture("resources/main-menu/cb_selected_texture.png");
    checkbox_2x->set_position(SCREEN_WIDTH - 15 - 20, SCREEN_HEIGHT - 15 - 20);
    checkbox_2x->set_text("2x", assets->get_font("d_font"), 20, sf::Text::Bold, sf::Color::White);

    // load default checkbox values
    if (config_defs.get("SCREEN_SCALE") == "1")
    {
        checkbox_1x->selected = true;
        checkbox_2x->selected = false;
    }
    else
    {
        checkbox_1x->selected = false;
        checkbox_2x->selected = true;
    }

    // reset mouse click delay  
    time_since_last_click = 0;
}

void MainMenuState::handle_input()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (sf::Event::Closed == event.type || exit_button->is_pressed())
        {
            window->close();
        }

        // check button delay
        if (time_since_last_click < CLICK_DELAY)
        {
            break;
        }

        if (play_button->is_pressed())
        {
            // Switch to game state
            add_state<GameState>(true);
        }

        time_since_last_click = 0;
    }
}

void MainMenuState::update(float delta_time)
{

    // configure scale 1x
    if (checkbox_1x->is_pressed())
    {
        checkbox_1x->selected = true;
        checkbox_2x->selected = false;

        config_defs.set("data/config.txt", "SCREEN_SCALE", "1");
        config_defs.load("data/config.txt");

        // set window scale
        sf::Vector2u w_size;
        w_size.x = SCREEN_WIDTH * 1;
        w_size.y = SCREEN_HEIGHT * 1;
        window->setSize(w_size);
    }

    // configure scale 2x
    if (checkbox_2x->is_pressed())
    {
        checkbox_1x->selected = false;
        checkbox_2x->selected = true;

        config_defs.set("data/config.txt", "SCREEN_SCALE", "2");
        config_defs.load("data/config.txt");

        // set window scale
        sf::Vector2u w_size;
        w_size.x = SCREEN_WIDTH * 2;
        w_size.y = SCREEN_HEIGHT * 2;
        window->setSize(w_size);
    }

    play_button->update();
    credits_button->update();
    exit_button->update();
    checkbox_1x->update(delta_time);
    checkbox_2x->update(delta_time);

    time_since_last_click += delta_time;
}

void MainMenuState::draw(float delta_time)
{
    window->clear(sf::Color(26, 26, 26));

    play_button->draw();
    credits_button->draw();
    exit_button->draw();

    checkbox_1x->draw();
    checkbox_2x->draw();

    window->draw(label_checkbox);
    window->draw(title);

    window->display();
}

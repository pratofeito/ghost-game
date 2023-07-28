#include "states/game-state.hpp"

void GameState::init()
{
    window->setFramerateLimit(60);

    // pause button
    assets->load_texture("pause_button", PAUSE_BUTTON);
    pause_button.setTexture(assets->get_texture("pause_button"));
    pause_button.setPosition(SCREEN_WIDTH - 55, 10);

    // set texture for each tile
    read_csv();
    assets->load_texture("tiles", TILES_PATH);
    for (int i = 0; i < NO_TILES; i++)
    {
        tiles[i].setTexture(assets->get_texture("tiles"));
        tiles[i].setTextureRect(sf::IntRect(55 * i, 0, 55, 32)); // Assume que os tiles estao dispostos horizontalmente na textura
    }

    // map view
    default_view = window->getView();
    view = sf::View(sf::FloatRect(200, 200, 320, 240)); // posso usar o .reset(). também o setCenter e setSize
    time_interval = 1;

    // init player
    player.hitbox.setSize(sf::Vector2f(PLAYER_SIZE_X, PLAYER_SIZE_Y));
    player.hitbox.setFillColor(sf::Color::White);
    player.grid_position.x = 7;
    player.grid_position.y = 3;

    // movement
    center = tile_position(player.grid_position.x, player.grid_position.y);
    pos_end = tile_position(player.grid_position.x, player.grid_position.y);    // player movement position
    moving = false;

    // init player movement position
    std::cout << center.x << " " << center.y << std::endl;
    std::cout << pos_end.x << " " << pos_end.y << std::endl;

    // init game objects (mudar o tamanho máximo da string)
    game_objects.assign(20, std::vector<GameObject *>(20, nullptr));
    std::cout << game_objects.size() << " " << game_objects[2].size() << std::endl;
    init_walls();
}

void GameState::handle_input()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            window->close();
        }

        if (input.is_sprite_clicked(this->pause_button, sf::Mouse::Left, *window))
        {
            // PAUSE
            add_state<PauseState>(false);
        }

        // zoom
        if (time_interval >= INTERVAL)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
            {
                view.zoom(0.85f);
                time_interval = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
            {
                view.zoom(1.15f);
                time_interval = 0;
            }
        }
    }

    // new input system using stack
    int last_key_pressed = update_control();

    // keys actions
    if (last_key_pressed == sf::Keyboard::Left)
    {
        if (player.facing == LEFT)
        {
            move_adjacent_tile(-1, 0);
        }

        player.facing = LEFT;
    }
    else if (last_key_pressed == sf::Keyboard::Right)
    {
        if (player.facing == RIGHT)
        {
            move_adjacent_tile(1, 0);
        }

        player.facing = RIGHT;
    }
    else if (last_key_pressed == sf::Keyboard::Up)
    {
        if (player.facing == FRONT)
        {
            move_adjacent_tile(0, -1);
        }

        player.facing = FRONT;
    }
    else if (last_key_pressed == sf::Keyboard::Down)
    {
        if (player.facing == BACK)
        {
            move_adjacent_tile(0, 1);
        }

        player.facing = BACK;
    }
}

void GameState::update(float delta_time)
{
    sf::Vector2f center_update = update_movement(delta_time);

    player.hitbox.setPosition(center_update.x, center_update.y);
    view.setCenter(center_update.x + (PLAYER_SIZE_X / 2), center_update.y + (PLAYER_SIZE_Y / 2));

    time_interval += delta_time;
}

void GameState::draw(float delta_time)
{
    window->clear(sf::Color(56, 42, 55));

    // view
    window->setView(view);

    // tiles
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < line; j++)
        {
            int type = map[i * line + j];
            if (type == -1)
                continue;
            tiles[type].setPosition(tile_position(j, i));
            window->draw(tiles[type]);
        }
    }

    // player
    window->draw(player.hitbox);

    // default view
    window->setView(default_view);

    window->draw(this->pause_button);
    window->display();
}

// ------------------ movement -----------------

void GameState::move_adjacent_tile(int x, int y)
{
    if (!moving)
    {
        // check if the movement is blocked
        if (game_objects[player.grid_position.x + x][player.grid_position.y + y] != nullptr)
        {
            if (game_objects[player.grid_position.x + x][player.grid_position.y + y]->collidable)
            {
                return;
            }
        }

        // continue movement
        sf::Vector2f pos_after_move = center + tile_position(x, y);
        moving = true;
        this->pos_start = center;
        this->pos_end = pos_after_move;
        moving_elapsed_time = 0;

        player.grid_position.x += x;
        player.grid_position.y += y;

        // debug
        std::cout << "facing: " << player.facing << std::endl;
        std::cout << player.grid_position.x << " " << player.grid_position.y << std::endl;
    }
}

sf::Vector2f GameState::update_movement(float delta_time)
{
    if (!moving)
    {
        return center;
    }

    sf::Vector2f transition_pos = center;
    moving_elapsed_time += delta_time;

    transition_pos.x += (moving_elapsed_time * (pos_end.x - pos_start.x)) / SPEED;
    transition_pos.y += (moving_elapsed_time * (pos_end.y - pos_start.y)) / SPEED;

    if (moving_elapsed_time >= SPEED)
    {
        moving = false;
        center = pos_end;
        return center;
    }

    return transition_pos;
}

// ------------------- stack -------------------

void GameState::push_stack(int input)
{
    if (key_stack.empty())
    {
        key_stack.push_back(input);
        return;
    }

    for (int i = 0; i < (int)key_stack.size(); i++)
    {
        if (key_stack[i] == input)
        {
            return;
        }
    }

    key_stack.push_back(input);
}

void GameState::del_stack(int input)
{
    for (int i = 0; i < (int)key_stack.size(); i++)
    {
        if (key_stack[i] == input)
        {
            key_stack.erase(key_stack.begin() + i);
        }
    }
}

int GameState::update_control()
{
    // left update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        push_stack(sf::Keyboard::Left);
    else
        del_stack(sf::Keyboard::Left);

    // right update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        push_stack(sf::Keyboard::Right);
    else
        del_stack(sf::Keyboard::Right);

    // up update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        push_stack(sf::Keyboard::Up);
    else
        del_stack(sf::Keyboard::Up);

    // down update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        push_stack(sf::Keyboard::Down);
    else
        del_stack(sf::Keyboard::Down);

    // return the last key pressed
    if (!key_stack.empty())
        return key_stack.back();
    else
        return 0;
}

// -------------------- map -------------------

void GameState::read_csv()
{
    // :p
    //	std::printf("abobora madura\n");

    std::FILE *f;
    if (!(f = std::fopen(MAP_PATH, "r")))
    {
        std::printf("error opening file " MAP_PATH "\n");
        std::exit(1);
    }

    int count = 0;
    if (std::fscanf(f, "%d", &map[count++]) != 1)
    {
        std::printf("bad map input\n");
        std::exit(1);
    }
    while (std::fscanf(f, ",%d", &map[count]) == 1)
    {
        count++;
    }
    line = count;
    column++;

    while (std::fscanf(f, "%d", &map[count]) == 1)
    {
        count++;
        for (int i = 0; i < line - 1; i++)
        {
            if (std::fscanf(f, ",%d", &map[count++]) != 1)
            {
                std::printf("bad map input\n");
                std::exit(1);
            }
        }
        column++;
    }

    for (int i = 0; i < line * column; i++)
    {
        // map[i]--;
        if (map[i] >= NO_TILES || map[i] < -1)
        {
            std::printf("invalid tile %d\n", map[i * line + column]);
            std::exit(1);
        }
    }
}

sf::Vector2f GameState::tile_position(int j, int i)
{
    float jj = (float)j;
    float ii = (float)i;
    sf::Vector2f v(TILE_W / 2 * jj - TILE_W / 2 * ii, TILE_H / 2 * jj + TILE_H / 2 * ii);
    return v;
}

// --------------- game objects ---------------

void GameState::init_walls()
{
    std::fstream file;
    file.open(MAP_PATH);

    int row = 0, column = 0;
    string line;

    while (getline(file, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '1')
            {
                // game_objects[row, column] = dynamic_cast<GameObject*>(new Wall());
                game_objects[column][row] = new Wall();
            }

            if (line[i] != ',')
            {
                column++;
            }
        }

        column = 0;
        row++;
    }
}
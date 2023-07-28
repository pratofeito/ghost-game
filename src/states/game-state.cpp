#include "states/game-state.hpp"


void GameState::init()
{
	config_defs.load("data/config.txt");
	read_map(config_defs.get("MAP_PATH").c_str());
	read_coll(config_defs.get("COLLISIONS_PATH").c_str());
	
	dialogue.read_file();
	
	
    window->setFramerateLimit(60);

    assets->load_texture("pause_button", PAUSE_BUTTON);
    pause_button.setTexture(assets->get_texture("pause_button"));
    pause_button.setPosition(SCREEN_WIDTH - 55, 10);
	assets->load_font("default_font", config_defs.get("DEFAULT_FONT_PATH"));
	
#ifdef DEBUG
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			coord[i][j].setFont(assets->get_font("default_font"));
			coord[i][j].setCharacterSize(8);
			std::sprintf(coord_s, "%d %d", i, j);
			coord[i][j].setString(sf::String(coord_s));
			coord[i][j].setPosition(tile_position(i, j)+sf::Vector2f(TILE_W/3.0f, TILE_H/3.0f));
		}
	}
#endif		
	
	
    // set texture for each tile
    assets->load_texture("tiles", config_defs.get("TILES_PATH"));
    for (int i = 0; i < NO_TILES; i++)
    {
        tiles[i].setTexture(assets->get_texture("tiles"));
        tiles[i].setTextureRect(sf::IntRect(55 * i, 0, 55, 32)); // Assume que os tiles estao dispostos horizontalmente na textura
    }

    // map view definition
    default_view = window->getView();
    view = sf::View(sf::FloatRect(200, 200, 320, 240)); // posso usar o .reset(). também o setCenter e setSize
    time_interval = 1;

    // init player
    player.setSize(sf::Vector2f(PLAYER_SIZE_X, PLAYER_SIZE_Y));
    player.setFillColor(sf::Color::White);
    player_tile.x = 10;
    player_tile.y = 10;
    moving = false;
    moving_elapsed_time = 0;

    // movement
    center = tile_position(player_tile.x, player_tile.y);

    // start player movement position
    pos_start = tile_position(player_tile.x, player_tile.y);
    pos_end = tile_position(player_tile.x, player_tile.y);
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
        move_adjacent_tile(-1, 0);
    }
    else if (last_key_pressed == sf::Keyboard::Right)
    {
        move_adjacent_tile(1, 0);
    }
    else if (last_key_pressed == sf::Keyboard::Up)
    {
        move_adjacent_tile(0, -1);
    }
    else if (last_key_pressed == sf::Keyboard::Down)
    {
        move_adjacent_tile(0, 1);
    }
}

void GameState::update(float delta_time)
{
    sf::Vector2f center_update = update_movement(delta_time);

    player.setPosition(center_update.x - (PLAYER_SIZE_X / 2), center_update.y - (PLAYER_SIZE_Y / 2));
    view.setCenter(center_update.x, center_update.y);

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
            tiles[type].setPosition(tile_position(i, j));
            window->draw(tiles[type]);
#ifdef DEBUG
			if((i<50)&&(j<50)){
				window->draw(coord[i][j]);
			}
#endif
        }
    }

    // player
    window->draw(player);

    // default view
    window->setView(default_view);

    window->draw(this->pause_button);
    window->display();
}

// ------------------- custom -------------------

void GameState::move_adjacent_tile(int x, int y)
{
    if (!moving)
    {
		player_tile += sf::Vector2i(-x, y);
		std::printf("%d %d\n", player_tile.x, player_tile.y);
        sf::Vector2f pos_after_move = center + tile_position(-x, y);
        moving = true;
        this->pos_start = center;
        this->pos_end = pos_after_move;
        moving_elapsed_time = 0;
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

void GameState::read_map(char const* path){

	std::FILE* f;
	if(!(f = std::fopen(path, "r"))){
		std::printf("error opening file %s\n", path);
		std::exit(1);
	}
	
	int count=0;
	if(std::fscanf(f, "%d", &map[count++])!=1){
		std::printf("bad map input\n");
		std::exit(1);
	}
	while(std::fscanf(f, ",%d", &map[count])==1){
		count++;
	}
	line = count;
	column++;
	while(std::fscanf(f, "%d", &map[count])==1){
		count++;
		for(int i=0;i<line-1;i++){
			if(std::fscanf(f, ",%d", &map[count++])!=1){
				std::printf("bad map input\n");
				std::exit(1);
			}
		}
		column++;
	}
	
	for(int i=0;i<line*column;i++){
		map[i]--;
		if(map[i]>=NO_TILES || map[i]<-1){
			std::printf("invalid tile %d\n", map[i*line+column]);
			std::exit(1);
		}
	}
}

void GameState::read_coll(char const* path){

	std::FILE* f;
	if(!(f = std::fopen(path, "r"))){
		std::printf("error opening file %s\n", path);
		std::exit(1);
	}
	
	for(int i=0;i<column;i++){
		if(std::fscanf(f, "%d", &coll[i*column])!=1){
			std::printf("bad collisions input\n");
			std::exit(1);
		}
		for(int j=1;j<line;j++){
			if(std::fscanf(f, ",%d", &coll[i*column+j])!=1){
				std::printf("bad collisions input\n");
				std::exit(1);
			}
		}
	}
}

sf::Vector2f GameState::tile_position(int i, int j)
{
    float jj = (float)j;
    float ii = (float)i;
    sf::Vector2f v(TILE_W / 2 * jj - TILE_W / 2 * ii, TILE_H / 2 * jj + TILE_H / 2 * ii);
    return v;
}

int GameState::tile_id(sf::Vector2i tile){
	return tile.x*line+tile.y;
}


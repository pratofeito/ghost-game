#include "states/game-state.hpp"

void GameState::init()
{
	read_csv(MAP_PATH, map);
    window->setFramerateLimit(60);

    assets->load_texture("pause_button", PAUSE_BUTTON);
    pause_button.setTexture(assets->get_texture("pause_button"));
    pause_button.setPosition(window->getSize().x - pause_button.getLocalBounds().width - 10, pause_button.getPosition().y + 10);

	assets->load_texture("tiles", TILES_PATH);
	for(int i=0;i<NO_TILES;i++){
		tiles[i].setTexture(assets->get_texture("tiles"));
		tiles[i].setTextureRect(sf::IntRect(55*i, 0, 55, 32)); // Assume que os tiles estao dispostos horizontalmente na textura
	}
//	std::printf("abobrinha\n");

    // view
    default_view = window->getView();
    view = sf::View(sf::FloatRect(200, 200, 320, 240)); // posso usar o .reset(). também o setCenter e setSize

    // init player
    player.setSize(sf::Vector2f(PLAYER_SIZE_X, PLAYER_SIZE_Y));
    player.setFillColor(sf::Color::White);

    center = sf::Vector2f(0.0f, 0.0f);

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
        if (input->is_sprite_clicked(this->pause_button, sf::Mouse::Left, *window))
        {
            // PAUSE
            add_state<PauseState>(false);
        }
        // zoom
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        {
            view.zoom(0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        {
            view.zoom(2);
        }
    }
	int rl=0, ud=0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		rl--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		rl++;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		ud--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		ud++;
	}		
	
	int pra_onde = rl*3+ud;
	
	t_antes = t_agora;
	t_agora = (float) clock.getElapsedTime().asMicroseconds();
	float dt = t_agora-t_antes;
	float px = 0, py = 0;
	switch(pra_onde){
		case 3:
			px += dt*1.45f;
			break;
		
		case 4:
			px += dt*1.375f;
			py += dt*0.8f;
			break;
		
		case 2:
			px += dt*1.375f;
			py -= dt*0.8f;
			break;
		
		case 1:
			py += dt*1.2f;
			break;
		
		case -1:
			py -= dt*1.2f;
			break;
		
		case -3:
			px -= dt*1.45f;
			break;
			
		case -2:
			px -= dt*1.375f;
			py += dt*0.8f;
			break;
		
		case -4:
			px -= dt*1.375f;
			py -= dt*0.8f;
			break;			
	}
	
	center.x += px*SPEED;
	center.y += py*SPEED;
}

void GameState::update(float delta_time)
{
    player.setPosition(center.x - (PLAYER_SIZE_X / 2), center.y - (PLAYER_SIZE_Y / 2));
    view.setCenter(center.x, center.y);
}

void GameState::draw(float delta_time)
{
    window->clear(sf::Color(56, 42, 55));

    // view
    window->setView(view);

	// tiles
	for(int i=0;i<column;i++){
		for(int j=0;j<line;j++){
			int type = map[i*line+j];
			if(type==-1) continue;
			tiles[type].setPosition(tile_position(i-column/2, j-column/2));
			window->draw(tiles[type]);
		}
	}

    // player
    window->draw(player);
    
    // default view
    window->setView(default_view);

    window->draw(this->pause_button);
    window->display();
}


void GameState::read_csv(char const* path, int* map_buf){

//	std::printf("abobora madura\n");
	std::FILE* f;
	if(!(f = std::fopen(path, "r"))){
		std::printf("error opening file %s\n", path);
		std::exit(1);
	}
	
	int count=0;
	if(std::fscanf(f, "%d", &map_buf[count++])!=1){
		std::printf("bad map input\n");
		std::exit(1);
	}
	while(std::fscanf(f, ",%d", &map_buf[count])==1){
		count++;
	}
	line = count;
	column++;
	while(std::fscanf(f, "%d", &map_buf[count])==1){
		count++;
		for(int i=0;i<line-1;i++){
			if(std::fscanf(f, ",%d", &map_buf[count++])!=1){
				std::printf("bad map input\n");
				std::exit(1);
			}
		}
		column++;
	}
	
	for(int i=0;i<line*column;i++){
		map[i]--;
		if(map[i]>=NO_TILES || map_buf[i]<-1){
			std::printf("invalid tile %d\n", map_buf[i*line+column]);
			std::exit(1);
		}
	}
}

sf::Vector2f GameState::tile_position(int i, int j){
	float jj = (float) j;
	float ii = (float) i;
	sf::Vector2f v(TILE_W/2*jj-TILE_W/2*ii,TILE_H/2*jj+TILE_H/2*ii);
	return v;
}



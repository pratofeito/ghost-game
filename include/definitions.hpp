/**
 * @file definitions.hpp
 * 
 * @brief General definitions used across the program
 * 
 */

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// splash screen
#define SPLASH_STATE_SHOW_TIME 1
#define SPLASH_SCENE_BACKGROUND_FILEPATH "resources/prato-logo.png"

// main menu
#define MAIN_MENU_BACKGROUND_FILEPATH "resources/main-menu.png"
#define MAIN_MENU_TITLE_FILEPATH "resources/main-menu.png"
#define MAIN_MENU_PLAY_BUTTON "resources/main-menu/play_btn.png"
#define MAIN_MENU_QUIT_BUTTON "resources/main-menu/quit_btn.png"

// game
#define GAME_BACKGROUND_FILEPATH "resources/splash.png"
#define PAUSE_BUTTON "resources/pause_btn.png"
#define MAP_PATH "resources/maps/big.csv"
#define TILES_PATH "resources/maps/isometric_tileset.png"
#define TILE_W 55.0f
#define TILE_H 32.0f
#define NO_TILES 2

#define PLAYER_SIZE_X 15
#define PLAYER_SIZE_Y 25

#define WIDTH SCREEN_WIDTH / TILE_SIZE
#define HEIGHT SCREEN_HEIGHT / TILE_SIZE
#define SPEED (1.0f/15000.0f)


// pause menu
#define PAUSE_BACKGROUND_FILEPATH "resources/pause_bg.png"
#define PAUSE_MENU_RESUME_BUTTON "resources/pause-menu/resume_btn.png"
#define PAUSE_MENU_HOME_BUTTON "resources/pause-menu/home_btn.png"

// defaults
#define DEFAULT_FONT_PATH "resources/fonts/VT323.ttf"

#endif

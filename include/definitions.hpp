/**
 * @file definitions.hpp
 * 
 * @brief General definitions used across the program
 * 
 */

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// window
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// splash screen
#define SPLASH_STATE_SHOW_TIME 1

// main menu
#define MAIN_MENU_BACKGROUND_FILEPATH "resources/main-menu.png"
#define MAIN_MENU_TITLE_FILEPATH "resources/main-menu.png"
#define MAIN_MENU_PLAY_BUTTON "resources/main-menu/play_btn.png"
#define MAIN_MENU_QUIT_BUTTON "resources/main-menu/quit_btn.png"

// game
#define GAME_BACKGROUND_FILEPATH "resources/splash.png"
#define PAUSE_BUTTON "resources/pause_btn.png"
#define MAP_PATH "resources/maps/map.csv"
#define TILES_PATH "resources/maps/isometric_tileset.png"
#define TILE_W 55.0f
#define TILE_H 32.0f
#define NO_TILES 2

#define PLAYER_SIZE_X 55
#define PLAYER_SIZE_Y 32
#define SPEED 0.5f

// pause menu
#define PAUSE_BACKGROUND_FILEPATH "resources/pause_bg.png"
#define PAUSE_MENU_RESUME_BUTTON "resources/pause-menu/resume_btn.png"
#define PAUSE_MENU_HOME_BUTTON "resources/pause-menu/home_btn.png"

#define DEFAULT_FONT "resources/fonts/oswald.ttf"
#define HANDWRITING_FONT "resources/fonts/covered_by_your_grace.ttf"

// dialog box
#define TOP_BOX_TEXTURE_PATH "resources/dialog/top-box.png"
#define BACKGROUNG_TEXTURE_PATH "resources/dialog/background.png"
#define OPTION_TEXTURE_PATH "resources/dialog/button.png"
#define OPTION_HOVER_TEXTURE_PATH "resources/dialog/button-hover.png"
#define OPTION_PRESSED_TEXTURE_PATH "resources/dialog/button-pressed.png"

#endif

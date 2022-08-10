#pragma once
#include<SDL.h>

#define         MENU_FONTNAME                 "fonts/vgafixr.ttf"
#define         MENU_FONT_HGT                 50
#define         MENU_FONT_VERTICAL_DISTANCE   80
#define         MENU_OPTIONS_NUM              3
const char      MENU_OPTIONS[][9] = { "start", "settings", "exit" };
const SDL_Color COLOR_OF_ACTIVE_OPTION = { 255, 0, 0, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION = { 150, 150, 220, 255 };

#define AMOUNT_ENEMY  12
#define ENEMY_TYPE    2
const char ENEMY_FILENAMES[ENEMY_TYPE][40] = {
	"enemy/enemy_1.png",
	"enemy/enemy_2.png"
};


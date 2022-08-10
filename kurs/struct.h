#pragma once
#include"Texture.h"
#include"config.h"
#include"Stack.h"

enum gameStates
{
	GAME_STATE_MENU = 0,
	GAME_STATE_PLAY = 1,
	GAME_STATE_SETTINGS = 2,
	GAME_STATE_EXIT = 3,
};
struct Enemy
{
	int mas[50];
	int type;

	float X;
	float Y;

	float HP;
	float speed;
	float direct;

	Texture texture_en;

	int damage;
	float Depth;
	unsigned int tmpTime = 0;
};

struct weapons
{
	float Depth;
	float damage;
	int mag_bull;
	int pellet;
	int range;
	int rate_of_fire;
};

struct
{
	// textures of options
	Texture textures[MENU_OPTIONS_NUM];
	// choice of texture option
	int choice = 0;
	// text block position of top
	int textBlockY;
	int lastKeyTick;
};

struct Player
{
	float X ;
	float Y ;
	float direct ;
	int score = 0;
	int mag;
	int HP=100;

	float FOV = 3.14159 / 6.0;
	float Depth = 12.0;
	float Speed = 0.75;
	int type_weapon=0;
};

struct RGB
{
	int red;
	int green;
	int blue;
};

struct KeysStatus
{
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool rechange = false;
	bool btnLeft = false;
	int  mouse_x;
	int  mouse_y;
};

struct Menu
{
	// textures of options
	Texture textures[MENU_OPTIONS_NUM];
	// choice of texture option
	int choice = 1;
	// text block position of top
	int textBlockY;
	int lastKeyTick;
};

struct Game {
	int winWidth = 120, winHeight = 40;

	bool       run = true;
	int        state = 0;
	SDL_Event  ev;
	KeysStatus keys;
	Texture    background;
	Player     player;
	Enemy      enemy[AMOUNT_ENEMY];
	weapons    weapons;
	Menu	   menu;
	RGB        rgb;

	//карта
	char map[100][101]{
		"##############################", //карта
		"#............................#",
		"#.##....############...###...#",
		"#..#...........##..#...###...#",
		"#..#...##......##..#...###...#",
		"#.##...##......#.............#",
		"#.##...##......#.............#",
		"#.#....#.......####...###..###",
		"###......########......#.....#",
		"##...................###.....#",
		"#......#########.......##....#",
		"#......#.......####.....#....#",
		"#......#.......#..#.....#....#",
		"#............................#",
		"#......#########.............#",
		"#..............####....####..#",
		"######...##########....#######",
		"#....#.......................#",
		"#.##....############...###...#",
		"#..#...........##..#...###...#",
		"#..#...##......##..#...###...#",
		"#.##...##......#.............#",
		"#.##...##......#.............#",
		"#.#....#.......####...###..###",
		"###......########......#.....#",
		"##...................###.....#",
		"#......#########.......##....#",
		"#......#.......####.....#....#",
		"#......#..........#.....#....#",
		"#............................#",
		"#......#########.............#",
		"#......................####..#",
		"##############################",
	};
	int map_height = 33; 
	int map_width = 30;
};

#include<iostream>
#include"players_func.h"
#include<SDL.h>
#include"Weapons.h"

void movement(Game& game,unsigned int RealTime)
{
	unsigned int del_time = 0;
	if (!game.keys.right && game.keys.left)  // поворот камеры
		game.player.direct -= (game.player.Speed * 0.15f);
	if (game.keys.right && !game.keys.left)
		game.player.direct += (game.player.Speed * 0.15f);
	if (game.keys.up && !game.keys.down) //движение
	{

		game.player.X += sinf(game.player.direct) * game.player.Speed * 0.25;
		game.player.Y += cosf(game.player.direct) * game.player.Speed * 0.25;
		if (game.map[(int)game.player.Y][(int)game.player.X] == '#' || game.map[(int)game.player.Y][(int)game.player.X] == '@')
		{

			game.player.X -= sinf(game.player.direct) * game.player.Speed * 0.25;
			game.player.Y -= cosf(game.player.direct) * game.player.Speed * 0.25;
		}
	}
	if (!game.keys.up && game.keys.down)
	{

		game.player.X -= sinf(game.player.direct) * game.player.Speed * 0.25;
		game.player.Y -= cosf(game.player.direct) * game.player.Speed * 0.25;
		if (game.map[(int)game.player.Y][(int)game.player.X] == '#' || game.map[(int)game.player.Y][(int)game.player.X] == '@')
		{

			game.player.X += sinf(game.player.direct) * game.player.Speed * 0.25;
			game.player.Y += cosf(game.player.direct) * game.player.Speed * 0.25;
		}
	}
	if (game.keys.btnLeft && (RealTime - del_time) >= game.weapons.rate_of_fire)
	{
		weapons_use(game, SDL_GetTicks());
		del_time = SDL_GetTicks();
	}
	if (game.keys.rechange)
	{
		weapons_type(game);
		rechange(game);
	}
}

void GamePrint(Game& game)
{
	SDL_DestroyTexture(game.texture.tex);
	char str[100];
	sprintf_s(str, "HP %03i", game.player.HP);
	game.texture = loadFont(str, MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT+30);
	SDL_Rect r = { 70, 1000, 0, 0 };
	r.w = game.texture.dstrect.w;
	r.h = game.texture.dstrect.h;
	SDL_RenderCopy(ren, game.texture.tex, NULL, &r);
	SDL_DestroyTexture(game.texture.tex);
	sprintf_s(str, "Ammo %02i", game.player.mag);
	game.texture = loadFont(str, MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT + 30);
	r = { 1600, 1000, 0, 0 };
	r.w = game.texture.dstrect.w;
	r.h = game.texture.dstrect.h;
	SDL_RenderCopy(ren, game.texture.tex, NULL, &r);
}

void Game_score(Game& game)
{
	int n = 0;
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (game.enemy[i].HP <= 0) n++;
	}
	game.player.score = n * 1000;
}

void SavePosition(Player player)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "wb") != 0)
	{
		printf("Could't open file 1.bin!\n");
		exit(1);
	}
	fprintf(f, "%f %f %f", player.X, player.Y, player.direct);
	fclose(f);
}


void ReadPosition(Player& player)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "rb") != 0)
	{
		printf("Could't open file 1.bin	!\n");
		exit(1);
	}
	fscanf_s(f, "%f %f %f", &player.X, &player.Y, &player.direct);
	fclose(f);
}

void LoadMap(Game& game)
{
	FILE* ft;
	if (fopen_s(&ft, "maps/map_1.txt", "rt") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d%d", &game.map_width, &game.map_height);

		for (int i = 0; i <= game.map_height; i++)
		{
			for (int j = 0; j <= game.map_width; j++)
				fscanf_s(ft, "%c", &game.map[i][j]);
			fscanf_s(ft, "\n");
		}

	}
}

void GameEnd(Game& game)
{
	if (game.player.HP <= 0)
		game.run = false;
}
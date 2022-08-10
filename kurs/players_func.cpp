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

void GameEnd(Game& game)
{
	if (game.player.HP <= 0)
		game.run = false;
}
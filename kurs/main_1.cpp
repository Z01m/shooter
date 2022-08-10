#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"struct.h"
#include"Enemy.h"
#include"Window.h"
#include"Game.h"

#include"Players_func.h"


SDL_Texture* pistol_texture; 
SDL_Texture* shot_gun_texture; 
SDL_Texture* Knife_texture; 
SDL_Texture* Machin_gun_texture;

int main(int argc, char* arg0s[])
{
	
	Game game;

	srand(time(0));
	ReadPosition(game.player);
	spawn_enemy(game);
	Init();
	GameInit(game);
	
	pistol_texture = SDL_CreateTextureFromSurface(ren, IMG_Load("pistol.png"));
	shot_gun_texture = SDL_CreateTextureFromSurface(ren, IMG_Load("shot_gun.png"));
	Machin_gun_texture = SDL_CreateTextureFromSurface(ren, IMG_Load("MachinGun.png"));
	Knife_texture = SDL_CreateTextureFromSurface(ren, IMG_Load("knife.png"));

	SDL_Event ev;
	unsigned int RealTime;
	enemyTexture(game);
	while (game.run)
	{
		RealTime = SDL_GetTicks();
		gameLoop(game, RealTime);
		

		SDL_Rect ref = { 1280,720,512,512 };
		if(game.state == GAME_STATE_PLAY)
		switch (game.player.type_weapon)
		{
			case 0:
			{
				SDL_RenderCopy(ren, pistol_texture, NULL, &ref);
			}
			break;
		case 1:
			{
				SDL_RenderCopy(ren, shot_gun_texture, NULL, &ref);
			}
		break;
		case 2:
			{
				SDL_RenderCopy(ren, Machin_gun_texture, NULL, &ref);
			}
		break;
		case 3:
			{
				SDL_RenderCopy(ren, Knife_texture, NULL, &ref);
			}
		break;
		}	
		

		
		SDL_RenderPresent(ren);
		SDL_Delay(50);
	}

	SavePosition(game.player);
	Game_score(game);
	printf("%d", game.player.score);
	DeInit(0);
	return 0;
}
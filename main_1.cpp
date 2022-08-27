#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"struct.h"
#include"Enemy.h"
#include"Window.h"
#include"Game.h"
#include"Weapons.h"
#include"Menu.h"
#include"Players_func.h"


SDL_Texture* pistol_texture; 
SDL_Texture* shot_gun_texture; 
SDL_Texture* Knife_texture; 
SDL_Texture* Machin_gun_texture;

int main(int argc, char* arg0s[])
{
	
	Game game;
	LoadMap(game, game.player.map_num);
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
	weapons_type(game);
	rechange(game);
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
	Game_score(game);
	char str[100];
		SDL_SetRenderDrawColor(ren, 0, 0, 89, 255);
		SDL_RenderClear(ren);
		sprintf_s(str, "Game Over\nScore %i\n", game.player.score);
		game.texture = loadFont(str, MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT + 30);
		SDL_Rect r = {(win_width - game.texture.dstrect.w)/2 , (win_height - game.texture.dstrect.h) / 2, 0, 0 };
		r.w = game.texture.dstrect.w;
		r.h = game.texture.dstrect.h;
		SDL_RenderCopy(ren, game.texture.tex, NULL, &r);
		SDL_DestroyTexture(game.texture.tex);
		SDL_RenderPresent(ren);
		SDL_Delay(3000);
	SavePosition(game.player);

	printf("%d", game.player.score);
	DeInit(0);
	return 0;
}
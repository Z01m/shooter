#include"Game.h"
#include"menu.h"
#include"enemy.h"
#include<SDL.h>
#include"Players_func.h"
#include"Weapons.h"

void GameInit(Game& game)
{
	game.run = true;
	MenuInit(game.menu);
}

void GameUpdate(Game& game, unsigned int RealTime)
{
	while (SDL_PollEvent(&game.ev))
	{
		switch (game.ev.type)
		{
		case SDL_QUIT:
			game.run = false;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&game.keys.mouse_x, &game.keys.mouse_y);
			break;

		case SDL_WINDOWEVENT:
			if (game.ev.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				game.winHeight = game.ev.window.data2;
				game.winWidth = game.ev.window.data1;
			}
			break;
		case SDL_KEYDOWN:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				game.run = false;
				break;
			case SDL_SCANCODE_S:
				game.keys.down = true;
				break;
			case SDL_SCANCODE_W:
				game.keys.up = true;
				break;
			case SDL_SCANCODE_A:
				game.keys.left = true;
				break;
			case SDL_SCANCODE_D:
				game.keys.right = true;
				break;
			case SDL_SCANCODE_1:

				game.player.type_weapon = 0;


				break;
			case SDL_SCANCODE_2:

				game.player.type_weapon = 1;


				break;
			case SDL_SCANCODE_3:

				game.player.type_weapon = 2;


				break;
			case SDL_SCANCODE_4:

				game.player.type_weapon = 3;


				break;
			case SDL_SCANCODE_R:
				game.keys.rechange = true;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_S:
				game.keys.down = false;
				break;
			case SDL_SCANCODE_W:
				game.keys.up = false;
				break;
			case SDL_SCANCODE_A:
				game.keys.left = false;
				break;
			case SDL_SCANCODE_D:
				game.keys.right = false;
				break;
			case SDL_SCANCODE_R:
				game.keys.rechange = false;
				break;

			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (game.ev.button.button == SDL_BUTTON_LEFT && GAME_STATE_PLAY)
				game.keys.btnLeft = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (game.ev.button.button == SDL_BUTTON_LEFT && GAME_STATE_PLAY)
				game.keys.btnLeft = false;
			break;
		}
	}
	weapons_type(game);
	movement(game, RealTime);

	switch (game.state)
	{
	case GAME_STATE_MENU:
		MenuProcess(game);
		break;
	case GAME_STATE_PLAY:
		run_enemy(game);
		enemy_damage(game, RealTime);
		GameEnd(game);
		break;
	case GAME_STATE_EXIT:
		game.run = false;
		break;
	}
}

void Game_draw_process(Game& game)
{
	SDL_Rect r = { 0,0,16,16 };
	for (int x = 0; x < game.winWidth; x += (r.w)) // x проходит по всей длине экрана с заданным шагом 
	{

		r.x = x;
		float fRayAngle = (game.player.direct - game.player.FOV / 2.0f) + ((float)x / (float)game.winWidth) * game.player.FOV;  //расчет каждого луча относительно x

		float fStepSize = 0.1f; // шаг на который увеличивается расстояние
		float fDistanceToWall = 0.0f; //дистанция до стены

		bool HitWall = false; // врезался ли в стену

		float fEyeX = sinf(fRayAngle);
		float fEyeY = cosf(fRayAngle);

		while (!HitWall && fDistanceToWall < game.player.Depth ) // пока луч не уперся в стену и меньше чем поле зрения цикл будет работать
		{
			fDistanceToWall += fStepSize;
			int nTestX = (int)(game.player.X + fEyeX * fDistanceToWall); // координаты точки считаются каждый шаг позже будут сравниваться с координатами стен
			int nTestY = (int)(game.player.Y + fEyeY * fDistanceToWall);
			if (nTestX < 0 || nTestX >= game.map_width || nTestY < 0 || nTestY >= game.map_height)
			{
				HitWall = true;		//если дистаниция больще чем видимость 
				fDistanceToWall = game.player.Depth;
			}
			else
			{
				if (game.map[(int)nTestY][(int)nTestX] == '#') // проверка на то что луч врезался в стену
				{
					HitWall = true;

				}
				
			}
		}

		int nCeiling = (float)(game.winHeight / 2.0) - game.winHeight / ((float)fDistanceToWall);//расчет линии неба или потолка(тут без разницы)
		int nFloor = game.winHeight - nCeiling + 48;//расчет линии пола
		// раскраска стен и неба
		if ( fDistanceToWall <= game.player.Depth / 4.0f) // ифы красят стены в зависимости от дальности в задданный цвет
		{
			game.rgb.red = 136;
			game.rgb.green = 69;
			game.rgb.blue = 53;
		}
		else if ( fDistanceToWall < game.player.Depth / 3.0f)
		{
			game.rgb.red = 99;
			game.rgb.green = 51;
			game.rgb.blue = 39;
		}
		else if ( fDistanceToWall < game.player.Depth / 2.0f)
		{
			game.rgb.red = 61;
			game.rgb.green = 31;
			game.rgb.blue = 24;
		}
		else if ( fDistanceToWall < game.player.Depth)
		{
			game.rgb.red = 26;
			game.rgb.green = 13;
			game.rgb.blue = 10;
		}
		else 
		{
			game.rgb.red = 138;
			game.rgb.green = 43;
			game.rgb.blue = 227;
		}



		for (int y = 0; y < game.winHeight; y += (r.h)) // проход по высоте экрана
		{
			r.y = y;
			if (y <= nCeiling) //пока y не опустился ниже уровня потолка будет окрашивать в цвет
			{
				SDL_SetRenderDrawColor(ren, 137, 43, 227, 255);
				SDL_RenderFillRect(ren, &r);
			}
			else if (y > nCeiling && y <= nFloor) //раскраска стен в заданный заранее
			{
				SDL_SetRenderDrawColor(ren, game.rgb.red, game.rgb.green, game.rgb.blue, 255);
				SDL_RenderFillRect(ren, &r);
			}
			else // пол
			{
				// раскраска пола в зависимости от его удаленности от игрока
				float b = 1.0f - (((float)y - game.winHeight / 2.0f) / ((float)game.winHeight / 2.0f));
				if (b < 0.25)		SDL_SetRenderDrawColor(ren, 34, 139, 34, 255);
				else if (b < 0.5)	SDL_SetRenderDrawColor(ren, 34, 129, 34, 255);
				else if (b < 0.75)	SDL_SetRenderDrawColor(ren, 34, 119, 34, 255);
				else if (b < 0.25)	SDL_SetRenderDrawColor(ren, 34, 109, 34, 255);
				else				SDL_SetRenderDrawColor(ren, 137, 43, 227, 255);
				SDL_RenderFillRect(ren, &r);
			}

		}

	}
	 r = { 0,0,4,4 }; // тут начинается отображение карты
	for (int x = 0; x < game.map_width; x++)
	{
		r.x = x * 12;
		for (int y = 0; y < game.map_height; y++)
		{
			r.y = y * 12;
			if (game.map[y][x] == '#')
			{
				SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
				SDL_RenderFillRect(ren, &r);
			}
			if (game.map[y][x] == '@')
			{
				SDL_SetRenderDrawColor(ren, 128, 0, 50, 255);
				SDL_RenderFillRect(ren, &r);
			}

		}
	}
	SDL_SetRenderDrawColor(ren, 0, 100, 0, 255);
	r.x = game.player.X * 12;
	r.y = game.player.Y * 12;
	SDL_RenderFillRect(ren, &r);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	r.y = win_height / 2;
	r.x = win_width / 2 + 1;
	SDL_RenderFillRect(ren, &r);
}

void GameDraw(Game& game)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 89, 255);
	SDL_RenderClear(ren);
	switch (game.state)
	{
	case GAME_STATE_MENU:
		MenuDraw(game.menu);
		break;
	case GAME_STATE_PLAY:
		Game_draw_process(game);
		enemy_on_window(game);
		
		break;
	}
}

void gameLoop(Game& game, unsigned int Realtime)
{
	
	GameUpdate(game,Realtime);
	GameDraw(game);
}
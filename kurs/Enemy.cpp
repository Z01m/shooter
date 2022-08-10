#include"struct.h"
#include"Enemy.h"
#include<iostream>
#include"Game.h"
#include"Texture.h"
#include"Stack.h"

void enemyTexture(Game& game)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
		game.enemy[i].texture_en = loadTexture(ENEMY_FILENAMES[game.enemy[i].type]);
}

void typeEnemy(Game& game)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
		if (i < AMOUNT_ENEMY / 2) game.enemy[i].type = 0;
		else game.enemy[i].type = 1;
}

void spawn_enemy(Game& game) //функция спавна противников
{
	typeEnemy(game);
	int amount = 0;
	int X, Y;
	do
	{
		X = rand() % (game.map_width);
		Y = rand() % (game.map_height);
		if (game.map[Y][X] != '#' && game.map[Y][X] != '@')
		{
			game.enemy[amount].X = X;
			game.enemy[amount].Y = Y;
			game.map[(int)game.enemy[amount].Y][(int)game.enemy[amount].X] = '@';
			amount++;
		}
	} while (AMOUNT_ENEMY > amount);

	for (int  i= 0; i < AMOUNT_ENEMY; i++)
	{
		switch (game.enemy[i].type)
		{
		case 0:
		{
			game.enemy[i].damage = 15;
			game.enemy[i].HP = 100;
			game.enemy[i].speed = 0.7;
			game.enemy[i].Depth = 8;
			game.enemy[i].direct = rand() % 3;
		}
		break;
		case 1:
		{
			game.enemy[i].damage = 20;
			game.enemy[i].HP = 200;
			game.enemy[i].speed = 0.7;
			game.enemy[i].Depth = 5;
			game.enemy[i].direct = rand() % 3;
		}
		break;
		}
	}
}
void run_enemy(Game& game)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		game.map[(int)game.enemy[i].Y][(int)game.enemy[i].X] = '.';

		game.enemy[i].X += sinf(game.enemy[i].direct) * game.enemy[i].speed * 0.25;
		game.enemy[i].Y += cosf(game.enemy[i].direct) * game.enemy[i].speed * 0.25;

		if (game.map[(int)game.enemy[i].Y][(int)game.enemy[i].X] == '#' ||
			game.map[(int)game.enemy[i].Y][(int)game.enemy[i].X] == '@')
		{

			game.enemy[i].X -= sinf(game.enemy[i].direct) * game.enemy[i].speed * 0.25;
			game.enemy[i].Y -= cosf(game.enemy[i].direct) * game.enemy[i].speed * 0.25;
			game.enemy[i].direct += 1;
		
		}
		if (game.enemy[i].HP >= 0)
		{

			game.map[(int)game.enemy[i].Y][(int)game.enemy[i].X] = '@';
		
		}
	}
}

void Draw_enemy(Game& game, Stack* s, int floor, int Ceiling)
{
	int tmp = floor - Ceiling;
	int w_1 = tmp * game.enemy->texture_en.w / game.enemy->texture_en.h;
	for (Elem* elem = s->top; elem; elem = elem->next)
	{
		SDL_Rect TEXen = { s->top->x,Ceiling,w_1,tmp };
		SDL_RenderCopy(ren, game.enemy[elem->number].texture_en.tex, NULL, &TEXen);
	};
}

void enemy_on_window(Game &game)
{
	Stack s;
	StackInit(&s);
	for (int x = 0; x < game.winWidth; x += 16) // x проходит по всей длине экрана с заданным шагом 
	{
		float fRayAngle = (game.player.direct - game.player.FOV / 2.0f) + ((float)x / (float)game.winWidth) * game.player.FOV;  //расчет каждого луча относительно x

		float fStepSize = 0.1f; // шаг на который увеличивается расстояние
		float fDistanceToWall = 0.0f; //дистанция до стены

		bool HitWall = false; // врезался ли в стену
		bool HitEnemy = false;// врезался ли луч в противника

		float fEyeX = sinf(fRayAngle);
		float fEyeY = cosf(fRayAngle);

		while (!HitWall && fDistanceToWall < game.player.Depth && !HitEnemy) // пока луч не уперся в стену и меньше чем поле зрения цикл будет работать
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
				if (game.map[(int)nTestY][(int)nTestX] == '@')// проверка на то что луч врезался в врага
				{
					for(int i=0;i<AMOUNT_ENEMY;i++)
						if ((int)nTestY == (int)game.enemy[i].Y && (int)nTestX == (int)game.enemy[i].X)
						{
							if (StackIsOrig(&s, i))
							{
								StackPush(&s, i, x);
								// передает номер противника и координаты пикселя 
								break;
							}
						}
					HitEnemy = true;
				}
			}
		}

		int nCeiling = (float)(game.winHeight / 2.0) - game.winHeight / ((float)fDistanceToWall);//расчет линии неба или потолка(тут без разницы)
		int nFloor = game.winHeight - nCeiling;//расчет линии пола
		Draw_enemy(game, &s, nFloor, nCeiling);

	}
	StackClear(&s);
}

void enemy_damage(Game& game, unsigned int RealTime)
{
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		for (int x = 0; x < game.winWidth; x += 16)
		{
			float fRayAngle = (game.player.direct - game.player.FOV / 2.0f) + ((float)x / (float)game.winWidth) * game.player.FOV;;
			float fStepSize = 1.f;
			float fDistanceToWall = 0.0f;
			bool HitPlayer = false;
			bool HitWall = false;
			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);
			int nTestX = 0;
			int nTestY = 0;


			while (fDistanceToWall < game.enemy[i].Depth && !HitPlayer && !HitWall)
			{
				fDistanceToWall += fStepSize;
				nTestX = (int)(game.enemy[i].X + fEyeX * fDistanceToWall);
				nTestY = (int)(game.enemy[i].Y + fEyeY * fDistanceToWall);
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

					if ((int)nTestY == (int)game.player.Y && (int)nTestX == (int)game.player.X && (RealTime - game.enemy[i].tmpTime) >= 5000)//проверка на поподание
					{
						game.player.HP -= game.enemy[i].damage;
						game.enemy[i].tmpTime = SDL_GetTicks();
						game.enemy[i].direct = fRayAngle;
						HitPlayer = true;
						break;
					}
				}

			}
		}
	}
}


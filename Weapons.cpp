#include"struct.h"
#include"Weapons.h"
#include<iostream>
#include"config.h"
void weapons_type(Game &game)
{
	switch (game.player.type_weapon)
	{
		case 0://пистолет
		{
			game.weapons.Depth = 6;
			game.weapons.damage = 12;
			game.weapons.mag_bull = 10;
			game.weapons.pellet = 1;
			game.weapons.range = 0;
			game.weapons.rate_of_fire = 1000;
		}
		break;
		case 1: //дробовик
		{
			game.weapons.Depth = 10;
			game.weapons.damage = 13;
			game.weapons.mag_bull = 6;
			game.weapons.pellet = 8;
			game.weapons.range = 0;
			game.weapons.rate_of_fire = 1800;
		}
		break;
		case 2: //автомат
		{
			game.weapons.Depth = 15;
			game.weapons.damage = 12;
			game.weapons.mag_bull = 30;
			game.weapons.pellet = 1;
			game.weapons.range = 0;
			game.weapons.rate_of_fire = 100;
		}
		break;
		case 3://rey gun
		{
			game.weapons.Depth = 1;
			game.weapons.damage = 999;
			game.weapons.mag_bull = 999999;
			game.weapons.pellet = 1;
			game.weapons.range = 0;
			game.weapons.rate_of_fire = 0;
		}
		break;
	}
}
void pistol(Game& game)
{
	float fRayAngle = game.player.direct;
	float fStepSize = 0.3f;
	float fDistanceToWall = 0.0f;
	bool HitEnemy = false;
	float fEyeX = sinf(fRayAngle);
	float fEyeY = cosf(fRayAngle);
	int nTestX = 0;
	int nTestY = 0;
	

	while (fDistanceToWall < game.weapons.Depth && !HitEnemy)
	{
		fDistanceToWall += fStepSize;
		nTestX = (int)(game.player.X + fEyeX * fDistanceToWall);
		nTestY = (int)(game.player.Y + fEyeY * fDistanceToWall);
		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			if ((int)nTestY == (int)game.enemy[i].Y && (int)nTestX == (int)game.enemy[i].X)//проверка на поподание
			{
				game.enemy[i].HP -= game.weapons.damage;
			}

		}
	}
}

void shot_gun(Game& game)
{
	srand(time(0));
	for (int i = 0; i < game.weapons.pellet; i++)
	{
		float fRayAngle = (game.player.direct - game.player.FOV / 2.0f) + (60 + rand()%10 - 5 / (float)game.winWidth) * game.player.FOV;
		float fStepSize = 0.1f;
		float fDistanceToWall = 0.0f;
		bool HitEnemy = false;
		float fEyeX = sinf(fRayAngle);
		float fEyeY = cosf(fRayAngle);
		int nTestX = 0;
		int nTestY = 0;
		while (fDistanceToWall < game.weapons.Depth && !HitEnemy)
		{
			fDistanceToWall += fStepSize;
			nTestX = (int)(game.player.X + fEyeX * fDistanceToWall);
			nTestY = (int)(game.player.Y + fEyeY * fDistanceToWall);

			for (int i = 0; i < AMOUNT_ENEMY; i++)
			{
				if ((int)nTestY == (int)game.enemy[i].Y && (int)nTestX == (int)game.enemy[i].X)
				{
					game.enemy[i].HP -= game.weapons.damage;
				}

			}
		}
	}
}

void MachinGun(Game& game, float fRayAngle)
{
	float fStepSize = 0.1f;
	float fDistanceToWall = 0.0f;
	bool HitEnemy = false;
	float fEyeX = sinf(fRayAngle);
	float fEyeY = cosf(fRayAngle);
	int nTestX = 0;
	int nTestY = 0;
	while (fDistanceToWall < game.weapons.Depth && !HitEnemy)
	{
		fDistanceToWall += fStepSize;
		nTestX = (int)(game.player.X + fEyeX * fDistanceToWall);
		nTestY = (int)(game.player.Y + fEyeY * fDistanceToWall);

		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			if ((int)nTestY == (int)game.enemy[i].Y && (int)nTestX == (int)game.enemy[i].X)//проверка на поподание
			{
				game.enemy[i].HP -= game.weapons.damage;
			}

		}
	}
}

void rechange(Game& game)//переписать на 3 типа поторонов
{
	weapons_type(game);
	game.player.mag = game.weapons.mag_bull;
}

void weapons_use(Game& game,int realTime)
{

	if(game.player.mag>0 && realTime - game.weapons.del_time >= game.weapons.rate_of_fire)
	{
		float fRayAngle = game.player.direct;

		
		switch (game.player.type_weapon)
		{
		case 0:
		{
			pistol(game);
		}
		break;
		case 1:
		{
			shot_gun(game);
		}
		break;
		case 2:
		{
			if (realTime - game.weapons.del_time <= 250)
			{
				fRayAngle = (game.player.direct - game.player.FOV / 2.0f) + (60 + rand() % 8 - 6 / (float)game.winWidth) * game.player.FOV;
				MachinGun(game, fRayAngle);
			}
			else
			{
				fRayAngle = game.player.direct;
				MachinGun(game, fRayAngle);
			}
			break;
		}
		case 3:
		{
			pistol(game);
		}
		break;
		}
		game.weapons.del_time = SDL_GetTicks();
		game.player.mag--;

	}
}
#pragma once
#include"struct.h"
void movement(Game& game, unsigned int RealTime);
void Game_score(Game& game);
void SavePosition(Player player);
void ReadPosition(Player& player);
void LoadMap(Game& game);
void GameEnd(Game& game);
void GamePrint(Game& game);
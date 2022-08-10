#pragma once
#include"struct.h"
void GameInit(Game& game);
void GameDraw(Game& game);
void GameUpdate(Game& game, unsigned int Realtime);
void Game_draw_process(Game& game);
void gameLoop(Game& game, unsigned int Realtime);
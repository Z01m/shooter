#pragma once
void spawn_enemy(Game& game);
void run_enemy(Game& game);
void enemy_on_window(Game& game);
void Draw_enemy(Game& game, Stack* s, int floor, int Ceiling);
void enemyTexture(Game& game);
void enemy_damage(Game& game, unsigned int RealTime);
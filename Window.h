#pragma once
#include <SDL.h>

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int win_width;
extern int win_height;

void Init();
void DeInit(int error);
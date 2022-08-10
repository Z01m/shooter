#pragma once
#include"struct.h"


void changeTextureOptionColor(Menu& menu);

void MenuInit(Menu& menu);

void MenuDestroy(Menu& menu);

bool isPointInRect(const SDL_Rect& rect, SDL_Point& point);

void MenuProcess(Game& game);

void MenuDraw(Menu& menu);
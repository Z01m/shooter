#include<SDL.h>
#include<stdio.h>
#include"Menu.h"
#include"Window.h"
#include"Texture.h"
#include"config.h"

void changeTextureOptionColor(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);

		if (i == menu.choice)
		{
			menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
		}
		else
		{
			menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION, MENU_FONT_HGT);
		}
	}
}

void MenuInit(Menu& menu)
{
	menu.ticks = SDL_GetTicks();

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
	}
	menu.textBlockY = (win_height - ((MENU_FONT_HGT + MENU_FONT_VERTICAL_DISTANCE) * MENU_OPTIONS_NUM - MENU_FONT_VERTICAL_DISTANCE)) / 2;
	changeTextureOptionColor(menu);
}

void MenuDestroy(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);
	}
}

bool isPointInRect(const SDL_Rect& rect, SDL_Point& point)
{
	return (rect.x <= point.x && point.x <= rect.x + rect.w) &&
		(rect.y <= point.y && point.y <= rect.y + rect.h);
}

void MenuProcess(Game& game)
{
	int ticks = SDL_GetTicks();
	int minTime = 200;

	// change choice for keyboard buttons
	if ((game.keys.up || game.keys.down) && ticks - game.menu.ticks >= minTime)
	{
		game.menu.ticks = ticks;
		if (game.keys.up)
		{
			game.menu.choice = game.menu.choice ? game.menu.choice - 1 : MENU_OPTIONS_NUM - 1;
			changeTextureOptionColor(game.menu);
		}
		if (game.keys.down)
		{
			game.menu.choice = (game.menu.choice + 1) % MENU_OPTIONS_NUM;
			changeTextureOptionColor(game.menu);
		}
	}

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		// change choice for option under mouse
		SDL_Point point = { game.keys.mouse_x, game.keys.mouse_y };
		bool cursorUnderTexture = isPointInRect(game.menu.textures[i].dstrect, point);
		if (cursorUnderTexture)
		{
			game.menu.choice = i;
			changeTextureOptionColor(game.menu);
		}

		bool oneOfBtns = (game.keys.btnLeft && cursorUnderTexture);
		if (oneOfBtns && ticks - game.menu.ticks >= MENU_DELAY_BUTTONS)
		{
			game.menu.ticks = ticks;
			game.state = game.menu.choice + 1;
		}
	}
}

void MenuDraw(Menu& menu)
{
	SDL_Rect drawRect = { 0, menu.textBlockY, 0, 0 };

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		drawRect.w = menu.textures[i].dstrect.w;
		drawRect.h = menu.textures[i].dstrect.h;
		drawRect.x = (win_width - drawRect.w) / 2;
		menu.textures[i].dstrect = drawRect;
		SDL_RenderCopy(ren, menu.textures[i].tex, NULL, &drawRect);
		drawRect.y += drawRect.h + MENU_FONT_VERTICAL_DISTANCE;

	}
}

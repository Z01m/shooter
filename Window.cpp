#include<stdio.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include"Window.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
int win_width = 1920, win_height = 1080;


void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
	{
		printf("Couldn't init SDL_IMAGE! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	if (TTF_Init())
	{
		printf("Couldn't init SDL_TTF! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
	if (res & IMG_INIT_PNG) printf("initialized PNG library\n"); else printf("couldn't init png library \n");
	if (res & IMG_INIT_PNG) printf("initialized JNG library\n"); else printf("couldn't init jng library \n");
	win = SDL_CreateWindow("BlazBlue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("Couldn't creat window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't creat renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}
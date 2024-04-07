#include "Foundation.h"

void INITIALIZE(FRAME_WORK* GAME)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
	{
		SDL_GetError();
		return;
	}
	GAME->State = TRUE;
	GAME->gameover = FALSE;
	GAME->quitgame = FALSE;
	GAME->backtomenu = FALSE;
	//initializeAudio();
	srand(time(NULL));

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_GetError();
		return;
	}

	
	if (TTF_Init() == -1)
	{
		TTF_GetError();
		return;
	}
	GAME->window = SDL_CreateWindow("PHIEU LUU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WEIGHT, SCREEN_HEIGHT , SDL_WINDOW_SHOWN);
	if (GAME->window == NULL) return;
	GAME->renderer = SDL_CreateRenderer(GAME->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (GAME->renderer == NULL) return;

	TTF_SetFontStyle(GAME->font, TTF_STYLE_BOLD);
	GAME->WHITE.r = 255;
	GAME->WHITE.g = 255;
	GAME->WHITE.b = 255;
	GAME->WHITE.a = 0;



}



void MANAGE_FRAME(int time_begin)
{
	int END_OF_TIME = SDL_GetTicks()-time_begin;

	if (END_OF_TIME < 1000 / FPS) SDL_Delay((1000 / FPS) - END_OF_TIME);
}

bool MANAGE_TIME(FRAME_WORK* GAME, Time* time_data)
{
	CALCULATION_TIME(time_data);
	DISPLAY_TIME(GAME, time_data);
	if (CHECK_TIME(time_data, GAME)) return true;
	return false;
	
}

 void CALCULATION_TIME(Time* time_data)
{
	time_t time_CURRENT = time(NULL);
	int time_ELAPSE = (int) difftime (time_CURRENT, time_data->TIME_START);
	if (time_ELAPSE >= (TIME_MINUTE * 60))
	{
		time_data->REMAIN = 0;
	}
	else {
		time_data->MINUTE_REMAIN = time_data->REMAIN / 60;
		time_data->SECOND_REMAIN = time_data->SECOND_REMAIN % 60;
	}
}

void DISPLAY_TIME(FRAME_WORK* GAME, Time* time_data)
{
	static Image DISPLAY;
	
	DISPLAY.rect.x = (SCREEN_WEIGHT - DISPLAY.rect.w) / 2;
	DISPLAY.rect.y = 15;
	static int LASTSEEN_TIME = 0;
	char NUMBER_PRINT[8];

	if (LASTSEEN_TIME != time_data->REMAIN)
	{
		LASTSEEN_TIME = time_data->REMAIN;
		snprintf(NUMBER_PRINT, sizeof(NUMBER_PRINT), "%02d:%02d", time_data->MINUTE_REMAIN, time_data->SECOND_REMAIN);
		SDL_Surface* surface = TTF_RenderText_Solid(GAME->font, NUMBER_PRINT, GAME->WHITE);

		if (surface == NULL) { TTF_GetError(); }

		if (DISPLAY.texture != NULL) SDL_DestroyTexture(DISPLAY.texture);

		DISPLAY.texture = SDL_CreateTextureFromSurface(GAME->renderer, surface);

		if (DISPLAY.texture = NULL)
		{
			SDL_GetError();
		}
		SDL_FreeSurface(surface);
	}
}
bool CHECK_TIME(Time* time_data, FRAME_WORK* game)
{
	if (time_data->REMAIN == 0)
	{
		printf("the time has run out!\n");
		HANDLE_GAME(game);
		return true;
	}
	return false;
 }
void DRAW(SDL_Renderer* renderer, int x, int y, int WEIGHT, int HEIGHT)
{
	SDL_Rect rect = { x,y,WEIGHT, HEIGHT};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
 }

 void HANDLE_GAME(FRAME_WORK* GAME)
 {
	 GAME->gameover = TRUE;
 }
 void DISPLAY_GAME(FRAME_WORK* GAME, Time* time_data)
 {
	 SDL_Texture* background = NULL;

	 if (time_data->REMAIN == 0)
	 {
		 background = IMG_LoadTexture(GAME->renderer, " .png");
		 if (!background)
		 {
			 IMG_GetError();
			 return;
		 }
	 }
	 else
	 {
		 background = IMG_LoadTexture(GAME->renderer, ".PNG");
		 if (!background)
		 {
			 IMG_GetError();
			 return;
		 }
	 }

	 SDL_Surface* OPTION_SURFACE_MENU = TTF_RenderText_Solid(GAME->font, "GO BACK TO MENU", GAME->WHITE);
	 SDL_Texture* OPTION_TEXTURE_MENU = SDL_CreateTextureFromSurface(GAME->renderer, OPTION_SURFACE_MENU);
	 SDL_Rect OPTION_RECT_MENU = { (SCREEN_WEIGHT - OPTION_SURFACE_MENU->w) / 2 , ((SCREEN_HEIGHT + 140) + OPTION_SURFACE_MENU->h) / 2, OPTION_SURFACE_MENU->w, OPTION_SURFACE_MENU->h };

	 SDL_Surface* OPTION_SURFACE_QUIT = TTF_RenderText_Solid(GAME->font, "Quit", GAME->WHITE);
	 SDL_Texture* OPTION_TEXTURE_QUIT = SDL_CreateTextureFromSurface(GAME->renderer, OPTION_SURFACE_QUIT);
	 SDL_Rect OPTION_RECT_QUIT = { (SCREEN_WEIGHT - OPTION_SURFACE_QUIT->w) / 2 , ((SCREEN_HEIGHT + 200) + OPTION_SURFACE_QUIT->h) / 2,OPTION_SURFACE_QUIT->w,OPTION_SURFACE_QUIT->h };


	 while (GAME->backtomenu == false && GAME->quitgame == false)
	 {
		 while (SDL_PollEvent(&GAME->EVENT))
		 {
			 if (GAME->EVENT.type == SDL_MOUSEBUTTONDOWN)
			 {
				 int mouseX, mouseY;
				 SDL_GetMouseState(&mouseX, &mouseY);
				 if (mouseX >= OPTION_RECT_MENU.x && mouseX <= OPTION_RECT_MENU.x + OPTION_RECT_MENU.w && mouseY >= OPTION_RECT_MENU.y && mouseY <= OPTION_RECT_MENU.y + OPTION_RECT_MENU.h)
				 {
					 GAME->backtomenu = TRUE;
				 }
				 else if (mouseX >= OPTION_RECT_QUIT.x && mouseX <= OPTION_RECT_QUIT.x + OPTION_RECT_QUIT.w && mouseY >= OPTION_RECT_QUIT.y && mouseY <= OPTION_RECT_QUIT.y + OPTION_RECT_QUIT.h)
				 {
					 GAME->quitgame = TRUE;
				 }
			 }
		 }

		 SDL_RenderCopy(GAME->renderer, background, NULL, NULL);
		 SDL_RenderCopy(GAME->renderer, OPTION_TEXTURE_MENU, NULL, &OPTION_RECT_MENU);
		 SDL_RenderCopy(GAME->renderer, OPTION_TEXTURE_QUIT, NULL, &OPTION_RECT_QUIT);
		 SDL_RenderPresent(GAME->renderer);

	 }


	 if (GAME->backtomenu)
	 {
		 GAME->State = TRUE;
		 GAME->gameover = FALSE;
		 GAME->backtomenu = false;
		 GAME->quitgame = false;
	 }
	 else if (GAME->quitgame)
	 {
		 GAME->quit = true;
	 }

	 SDL_FreeSurface(OPTION_SURFACE_MENU);
	 SDL_FreeSurface(OPTION_SURFACE_QUIT);
	 SDL_DestroyTexture(background);
	 SDL_DestroyTexture(OPTION_TEXTURE_MENU);
	 SDL_DestroyTexture(OPTION_TEXTURE_QUIT);
 }
#pragma once
#ifndef FOUNDATION_H_
#define FOUNDATION_H_

#include<SDL.h>
#include<Windows.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<stdbool.h>
#include<string>
#include<vector>
#include<amaudio.h>
#include<cstdlib>
#include<ctime>
#include<time.h>

using namespace std;

#define SCREEN_WEIGHT 1280
#define SCREEN_HEIGHT 720 
#define FPS 60
#define TIME_MINUTE 5

const int screenn_pp = 30;

const int color_R = 157;
const int color_G = 175;
const int color_B = 180;

const int RENDER_DRAW_COLOR = 255;




static vector <vector <long long> > map;



#define TILE_SIZE 30   

#define Map_x 200
#define Map_y 70

#define tocdoroi 0.9
#define tocdoroi_max 3
#define speed_player 1


typedef struct 
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color WHITE;
	SDL_Event EVENT;
	bool State;
	bool quit;
	bool MUTE;
	bool gameover;
	bool backtomenu;
	bool quitgame;

} FRAME_WORK;

typedef struct
{
	bool active;
	SDL_Texture* texture;
	SDL_Rect rect;

} Image;

typedef struct
{
	 time_t TIME_START;
	int REMAIN;
	int MINUTE_REMAIN;
	int SECOND_REMAIN;

} Time;


void INITIALIZE(FRAME_WORK* GAME);
void MANAGE_FRAME(int time_begin);
bool MANAGE_TIME(FRAME_WORK* GAME, Time* time_data);
 void CALCULATION_TIME(Time* time_data);
 void DISPLAY_TIME(FRAME_WORK* GAME, Time* time_data);
 bool CHECK_TIME(Time* time_data, FRAME_WORK* game);
 void DRAW(SDL_Renderer* renderer, int x, int y, int WEIGHT ,int HEIGHT);
 void HANDLE_GAME(FRAME_WORK* GAME);
 void DISPLAY_GAME(FRAME_WORK* GAME, Time* time_data);
#endif // !FOUNDATION_H_

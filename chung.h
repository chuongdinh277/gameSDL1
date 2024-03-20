#pragma once

#ifndef Chung_H_

#include <SDL.h>
#include<Windows.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<cstdio>


using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int screen_chieudai = 1200;
const int screen_chieurong = 600;
const int screenn_pp = 30;

const int color_R = 157;
const int color_G = 175;
const int color_B = 180;

const int RENDER_DRAW_COLOR = 255;



static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Texture* treeTexture;
 
static vector <vector <long long> > map;



#define TILE_SIZE 30   

#define Map_x 200
#define Map_y 70

#define tocdoroi 0.9
#define tocdoroi_max 3
#define speed_player 1

typedef struct Map
{
	 int start_x_;
	 int start_y_;

	 int max_x_;
	 int max_y_;

	 int F[Map_y][Map_x];

	 char* file_name;
};

typedef struct dauvao
{
	int left;
	int right;
	int up;
	int down;
	int jump;
};

#endif 

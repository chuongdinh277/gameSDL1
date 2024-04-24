#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "audio.h"

#define SCREEN_WIDTH  1280 // chiều rộng màn hình
#define SCREEN_HEIGHT 720 // chiều cao màn hình

#define FPS 60

#define TIMER_MINUTES 2

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color white;
    SDL_Event event;
    bool MENU_STATE;
    bool QUIT;
    bool MUTE;
    bool GAMEOVER;
    bool BACK_MENU;
    bool QUIT_GAME;
    bool PAUSE;
    bool Win;
} FRAMEWORK;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Camera;

typedef struct {
    bool active;
    SDL_Texture* texture;
    SDL_Rect rectangle;
} Image;

typedef struct {
    time_t  TIME_START;
    int TIME_REMAIN; 
    int MINUTE_REMAIN;
    int SECOND_REMAIN;
} Timer; 
void INITIALIZE(FRAMEWORK* GAME); // khởi tạo ban đầu cho game cửa sổ , v.v
void MANAGE_FRAME(int time_begin);
void manageTimer(FRAMEWORK* game, Timer* time_Data);
static void CALCULATE_TIME(Timer* time_Data);//tính toán phút giây cho game
static void DISPLAY_TIME(FRAMEWORK* game, Timer* time_Data);//vẽ thời gian lên màn hình
static void DRAW_RECT(SDL_Renderer* renderer, int x, int y, int w, int h);
void DISPLAY_GAMEOVER(FRAMEWORK* game, Timer* time_Data);//xử lí game over

#endif
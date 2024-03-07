

#ifndef   COMMON_FUNCTION_H_
#define  COMMON_FUNCTION_H_ 


#include <Windows.h>
#include <string>
#include < SDL.h>
#include < SDL_mixer.h>
#include <SDL_ttf.h>
#include<SDL_image.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;



const int SCREEN_W = 1200;
const int SCREEN_H = 600;
const int SCREEN_BPP = 32;



const int COLOR_KEY_R = 157;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;




#endif
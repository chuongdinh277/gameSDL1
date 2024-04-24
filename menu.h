#pragma once
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <string.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "foundation.h"
#include "player.h"
#define MAX_NUMBER_OF_TEXT_BOXES 8
#define SPACING_BETWEEN_TEXT_BOXES 36
#define LOCATION_ADJUSTMENT 120
#define MAX_INPUT_LENGTH 15

static int PLAYER_NUMBER;

using namespace std;
typedef struct 
{
    const char* options[MAX_NUMBER_OF_TEXT_BOXES];
    char imageFilePath[50];   
} Menu;

int manageMenu(FRAMEWORK* game,  Player players);// xây dựng lớp menu
int displayOptions(FRAMEWORK* game, Menu* menu); // xử lí nhận sự kiện chuột
 void prepareTextBoxesToBeShown(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]);//xây dựng các lựa chọn
 void destroyBoxTextures(Menu* menu, SDL_Texture* textBoxTexture[]);
 void updateBoxContent(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]);
 void handleMenuEntry(int* scene, FRAMEWORK* game);//lớp menu bên ngoài
  int handleHostGameOption(int* scene, FRAMEWORK* game);//play game 
  void  Rule_Option(int* scene, FRAMEWORK* game);// luật chơi
 void handleSettingsOption(int* scene, FRAMEWORK* game);// setting bật tắt âm thanh cho game


#endif
#pragma once
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <string.h>
#include "base.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "foundation.h"
#include "player.h"
#define MAX_NUMBER_OF_TEXT_BOXES 8
#define SPACING_BETWEEN_TEXT_BOXES 36
#define LOCATION_ADJUSTMENT 120
#define MAX_INPUT_LENGTH 15


using namespace std;
typedef struct 
{
    const char* options[MAX_NUMBER_OF_TEXT_BOXES];
    char imageFilePath[50];   
} Menu;

int manageMenu(FRAMEWORK* game,  Player players);
int displayOptions(FRAMEWORK* game, Menu* menu);
 void prepareTextBoxesToBeShown(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]);
 void destroyBoxTextures(Menu* menu, SDL_Texture* textBoxTexture[]);
 void updateBoxContent(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]);
 void handleMenuEntry(int* scene, FRAMEWORK* game);
  int handleHostGameOption(int* scene, FRAMEWORK* game);
  void  Rule_Option(int* scene, FRAMEWORK* game);
 void handleSettingsOption(int* scene, FRAMEWORK* game);
 void handlePauseOption(int* scene, FRAMEWORK* game);

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "foundation.h"
#include "map.h"
#include <string>
#include <string.h>
#include "base.h"

#define PLAYER_FRAME_WIDTH 32
#define PLAYER_FRAME_HEIGHT 32
#define Default_Speed 5

using namespace std;

typedef struct {
    int player;
    SDL_Texture* spriteSheetTexture;
    SDL_Rect spriteClip[12];
    SDL_Rect position;
    int frame;
    int speed;
    bool captured;
    bool frozen;
    bool movementKeysReversed;
    bool up;
    bool down;
    bool left;
    bool right;
    bool hasPerk;
    time_t perkStartTime;
    bool No;
    // int baseSpeed;
    // int boostedSpeed;
    // Uint32 speedBoostStartTime;
} Player;

static Player createPlayer(SDL_Renderer* renderer, string playerModel, int positionX, int positionY,Player &playerX);
void renderPlayers(FRAMEWORK game, Player players);
void handleInput(FRAMEWORK* game, Player& player, Camera &camera);
void getMap(Camera &camera, Player &player);

Player loadPlayers(SDL_Renderer* renderer, Player players, int PLAYER_NUMBER,int x_pos,int y_pos);
#endif
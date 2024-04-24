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
    int hasPerk;
    time_t perkStartTime;
    bool No;
    bool GameOver;
    bool boom;
    int blood;

    int start_speed;
    int end_speed;

    int start_blood;
    int end_blood;
    bool battu;
    bool bum_bum_no;
} Player;
typedef struct
{
    SDL_Texture* bom_texture;
    SDL_Texture* Bom_Bom;
    SDL_Rect position;
    SDL_Rect position_bomno;
    int phamvi;
    int x_pos;
    int y_pos;
}BOM;


static Player createPlayer(SDL_Renderer* renderer, string playerModel, int positionX, int positionY,Player &playerX);//load nhân vật
void renderPlayers(FRAMEWORK game, Player players);//vẽ nhân vật
void handleInput(FRAMEWORK* game, Player& player, Camera &camera, BOM &bom);// xử lí sự kiện cho nhân vật
void checkMap(Camera& camera, Player &player);//check Map
int checktieMap(int x, int y);// check các ô trong tieMap
Player loadPlayers(SDL_Renderer* renderer, Player players, int PLAYER_NUMBER,int x_pos,int y_pos);//load ảnh nhân vật

//xử lí boom
void Render_Bom(SDL_Renderer* renderer,  BOM &bom);
void Bom_movie(BOM& bom, Camera camera);
void Render_bumbum(SDL_Renderer* renderer, BOM &bom);
void Move_Player(Player& player, Camera& camera, SDL_Renderer* renderer);

#endif
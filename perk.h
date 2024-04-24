#pragma once
#ifndef PERK_H
#define PERK_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "player.h"

#define perk_duration 5
#define DEFAULT_SPEED 2
#define PERK_WIDTH 32
#define PERK_HEIGHT 32
#define SPEED_BOOST_AMOUNT 1

typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    bool check;
    int cc;
    time_t respawnTime;
    int x_pos; int y_pos;

} Perk;

void renderPerk(SDL_Renderer* renderer, Perk* perk, Player& player, Camera* camera, int sc); // load các perk và random vị trí
void random_perk(Perk& perk, int x, int y); // random vị trí
void perk_movie(Perk& perk, Camera camera); // cập nhật perk khi nhân vật di chuyển


#endif

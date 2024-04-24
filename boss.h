
#ifndef BOSS_H_
#define BOSS_H_


#include"foundation.h"
#include"player.h"


#define Boss_Speed 2

typedef struct 
{
    int frame;
    SDL_Texture* monster_texture;
    SDL_Rect sprite_clip[24];
    SDL_Rect position;
    int status;
    int speed;
    int x_pos;
    int y_pos;
    int x_val;
    int y_val;

    bool up;
    bool down;
    bool left;
    bool right;
} Boss;

typedef struct
{
    int y;
    int x;
} Vitri;

void Find_hunter(Boss& monster, Player& player, FRAMEWORK* game);
int ktkc(Vitri Boss, Vitri Hunter);
void boss_Move(Boss& Mos, Camera camera);
void Random(Boss& mos, int x, int y);
void render_boss(FRAMEWORK game, Boss& monster);

void Atrack(Boss& monster);

#endif  

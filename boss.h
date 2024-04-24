
#ifndef BOSS_H_
#define BOSS_H_


#include"foundation.h"
#include"player.h"


#define Boss_Speed 1 // tốc độ của boss

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

    bool kt;
    bool check;
} Boss;

typedef struct
{
    int y;
    int x;
} Vitri;
void Find_hunter(Boss& monster, Player& player, FRAMEWORK* game); //con boss sẽ di chuyển tìm người
int ktkc(Vitri Boss, Vitri Hunter); // tính khoảng cách boss và nhân vật
void boss_Move(Boss& Mos, Camera camera); //cập nhật hình ảnh vị trí cho boss
void Random(Boss& mos, int x, int y); // khởi tạo boss
void render_boss(FRAMEWORK game, Boss& monster);// load ảnh cho boss


#endif  

#include "boss.h"
#include <iostream>
#include<vector>

void Random(Boss &Mos,int x,int y) {
	Mos.x_pos = x;
	Mos.y_pos = y;
	Mos.position.h = 32;
	Mos.position.w = 32;
	int frame_c = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Mos.sprite_clip[frame_c].x = j * 32 ;
			Mos.sprite_clip[frame_c].y = i * 32 ;
			Mos.sprite_clip[frame_c].w = 32;
			Mos.sprite_clip[frame_c].h = 32;
			frame_c++;
		}
	}
	Mos.frame = 0;
	Mos.speed = Boss_Speed;
}
void boss_Move(Boss& Mos, Camera camera)
{
	Mos.position.x = - camera.x + Mos.x_pos+ Mos.x_val;
	Mos.position.y = - camera.y + Mos.y_pos+ Mos.y_val;

}
void render_boss(FRAMEWORK game, Boss &monster)
{
	monster.monster_texture = IMG_LoadTexture(game.renderer, "resources/monster.png");
	SDL_Rect boss_position = monster.position;
}
void Find_hunter(Boss &monster, Player& player , FRAMEWORK* game)
{
	int frame = monster.frame;
	Vitri Mos, hunter;
	Mos.x = monster.position.x;
	Mos.y = monster.position.y;

	hunter.x = player.position.x;
	hunter.y = player.position.y;

	int res = ktkc(Mos, hunter);
	if (res <= 200)
	{
	if (Mos.x > hunter.x) monster.x_val -=Boss_Speed;
	else if(Mos.x<hunter.x)  monster.x_val += Boss_Speed;
	if (Mos.y > hunter.y) monster.y_val -= Boss_Speed;
	else if (Mos.y < hunter.y) monster.y_val += Boss_Speed;
	}

	if (Mos.x == hunter.x && Mos.y == hunter.y)
	{
		if(player.battu==false  && monster.check==true) player.blood -= 1;
	}
	SDL_Rect position = monster.position;
	SDL_RenderCopy(game->renderer, monster.monster_texture, &monster.sprite_clip[frame], &position);
}
int ktkc(Vitri Boss, Vitri Hunter)
{
	int res = abs((Hunter.x - Boss.x)) + abs(Hunter.y-Boss.y);
	return res;

}
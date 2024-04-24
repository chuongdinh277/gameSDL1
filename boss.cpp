#include "boss.h"
#include <iostream>
#include<vector>


void  Random(Boss &Mos,int x,int y) {
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
	//cout << x << " " << y << '\n';
	//cout << Mos.position.x << " " << Mos.position.y << '\n';
	Mos.frame = 0;
	Mos.speed = Boss_Speed;
}
void boss_Move(Boss& Mos, Camera camera)
{
	Mos.position.x = - camera.x + Mos.x_pos+ Mos.x_val;
	Mos.position.y = - camera.y + Mos.y_pos+ Mos.y_val;
	//cout << Mos.position.x << " " << Mos.position.y << '\n';

}
void render_boss(FRAMEWORK game, Boss &monster)
{
	//Random_position(game.renderer, &monster);
	monster.monster_texture = IMG_LoadTexture(game.renderer, "resources/monster.png");
	SDL_Rect boss_position = monster.position;
	
	//SDL_RenderCopy(game.renderer, monster.monster_texture, &monster.sprite_clip[monster.frame], &boss_position);
	//SDL_RenderCopyEx(game.renderer,monster.monster_texture, &monster.sprite_clip[monster.frame], &boss_position, 0, NULL, SDL_FLIP_NONE);
}
void Find_hunter(Boss &monster, Player& player , FRAMEWORK* game)
{
	int frame = monster.frame;
	Vitri Mos, hunter;
	//cout << monster.position.x << " " << monster.position.y << '\n';
	//cout << Mos.x << '\n';

	Mos.x = monster.position.x;
	Mos.y = monster.position.y;

	hunter.x = player.position.x;
	hunter.y = player.position.y;

	int res = ktkc(Mos, hunter);
	if (res <= 500)
	{

	if (Mos.x > hunter.x) monster.x_val -=Boss_Speed;
	else if(Mos.x<hunter.x)  monster.x_val += Boss_Speed;
	
	if(Mos.y>hunter.y) monster.y_val -= Boss_Speed;
	else if (Mos.y < hunter.y) monster.y_val += Boss_Speed;

	}

	
	/*int Ans = ktkc(Mos, hunter);
	
	for (int huong_dichuyen = 0; huong_dichuyen < 4; huong_dichuyen++)
	{
		if (huong_dichuyen == 0)
		{
			Mos.y -= Boss_Speed;
			int res = ktkc(Mos, hunter);
			if (res < Ans)
			{
				frame = 12;
				monster.up = true; monster.down = false; monster.left = false; monster.right = false;
			}
		}
		if (huong_dichuyen == 1)
		{
			Mos.y += Boss_Speed;
			int res = ktkc(Mos, hunter);
			if (res < Ans)
			{
				frame = 0;
				monster.up = false; monster.down = true; monster.left = false; monster.right = false;
			}
		}
		if (huong_dichuyen == 2)
		{
		Mos.x += Boss_Speed;
		int res = ktkc(Mos, hunter);
			if (res < Ans)
			{
				frame = 18;
				monster.up = false; monster.down = false; monster.left = false; monster.right = true;
			}
		}
		if (huong_dichuyen == 3)
		{
			Mos.x -= Boss_Speed;
			int res = ktkc(Mos, hunter);
			if (res < Ans)
			{
				frame = 12;
				monster.up = false; monster.down = false; monster.left = true; monster.right = false;
			}
		}
	}
	if (monster.up == true)
	{
		frame++;
		if (frame >= 17) frame = 12;
	}
	else if (monster.down == true)
	{
		frame++;
		if (frame >= 5) frame = 0;
	}
	else if (monster.left == true)
	{
		frame++;
		if (frame >= 11) frame = 6;
	}
	else if (monster.right == true)
	{
		frame++;
		if (frame >= 23) frame = 18;
	}
	*/
	

	SDL_Rect position = monster.position;
	SDL_RenderCopy(game->renderer, monster.monster_texture, &monster.sprite_clip[frame], &position);
}
int ktkc(Vitri Boss, Vitri Hunter)
{
	int res = abs((Hunter.x - Boss.x)) + abs(Hunter.y-Boss.y);
	return res;

}
void Atrack(Boss monster);
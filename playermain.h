#pragma once


#ifndef PLAYER_MAIN_H_

#define PLAYER_MAIN_H_

#include "Chung.h"
#include "base.h"



class playermain : public base
{
public:
	playermain();
	~playermain();

	enum Walktype
	{
		Walk_right = 0,
		Walk_left = 1,
		Walk_up = 2,
		Walk_down = 3,
	};

	 int checkomap(const int& x, const int& y, Map& map_data);
	bool Loadanh(SDL_Renderer* screen, string path);
	void Show(SDL_Renderer* des);

	void button(SDL_Event event, SDL_Renderer* screen);
	void set_clip(); 

	void nhanvatdichuyen(Map& map_data );
	void checkvachammap(Map& map_data);
	void Setmaptheonhanvat(const int map_x, const int map_y)
	{
		MAPP_X = map_x;
		MAPP_Y = map_y;
	};
	void Setthongsomap(Map& map_data);

private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	SDL_Rect frame[8];
	SDL_Rect Frame2_thuong_[8];
	SDL_Rect Frame2_kiem_[8];
	
	dauvao input_type;
	int trangthai;
	int status;

	int status_chiendau=0;
	bool vacham;

	int MAPP_X;
	int MAPP_Y;
};



#endif 

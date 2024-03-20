#include "playermain.h"
#include"base.h"

playermain::playermain()
{
	status_chiendau = 0;
	trangthai = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;

	width_frame = 0;
	height_frame = 0;

	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	status = -1;
	vacham = false;

	MAPP_X = 0;
	MAPP_Y = 0;
}

playermain::~playermain()
{
}


bool playermain::Loadanh(SDL_Renderer* screen, string path)
{
	bool ret = base::Loadanh(screen, path);

	if (ret == true)
	{
		width_frame = rect_.w / 9;
		height_frame = rect_.h;
	}
	return ret;
}

void playermain::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		if (status_chiendau == 0)
		{
			for (int i = 0; i < 9; ++i)
			{
				frame[i].x = i * width_frame;
				frame[i].y = 0;
				frame[i].w = width_frame;
				frame[i].h = height_frame;
			}
		}
		else if (status_chiendau == 1)
		{
			for (int i = 0; i < 8; ++i)
			{
				Frame2_kiem_[i].x = i * width_frame;
				Frame2_kiem_[i].y = 0;
				Frame2_kiem_[i].w = width_frame;
				Frame2_kiem_[i].h = height_frame;
			}
		}
		else if (status_chiendau == 2)
		{
			for (int i = 0; i < 6; ++i)
			{
				Frame2_thuong_[i].x = i * width_frame;
				Frame2_thuong_[i].y = 0;
				Frame2_thuong_[i].w = width_frame;
				Frame2_thuong_[i].h = height_frame;
			}
		}
	}
}


void playermain::Show(SDL_Renderer* des)
{
	if (status_chiendau == 0)
	{
    if (status == Walk_left) { Loadanh(des, "nhanvat//left.png"); }

	else if (status == Walk_right) { Loadanh(des, "nhanvat//right.png"); }

	else if (status == Walk_up) { Loadanh(des, "nhanvat//up.png"); }

	else if(status==Walk_down)
	{
		Loadanh(des, "nhanvat//down.png");
	}

	if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1)
	{
		trangthai++;
	}
	 if (trangthai > 9) trangthai = 0;
	 rect_.x = x_pos - MAPP_X;
	 rect_.y = y_pos - MAPP_Y;

SDL_Rect* current_clip = &frame[trangthai];
SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame,height_frame };

SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
	
	if (status_chiendau == 1)
	{
		if (status == Walk_left) { Loadanh(des, "nhanvat//cleft.png"); }

		else if (status == Walk_right) { Loadanh(des, "nhanvat//cright.png"); }

		else if (status == Walk_up) { Loadanh(des, "nhanvat//cup.png"); }

		else
		{
			Loadanh(des, "nhanvat//cdown.png");
		}

		if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1)
		{
			trangthai++;
		}
		else if (trangthai > 8) trangthai = 0;
		else trangthai = 0;

		rect_.x = x_pos-MAPP_X;
		rect_.y = y_pos-MAPP_Y;

		SDL_Rect* current_clip = &Frame2_thuong_[trangthai];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame,height_frame };

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}


	if (status_chiendau == 2)
	{
		if (status == Walk_left) { Loadanh(des, "nhanvat//kleft.png"); }

		else if (status == Walk_right) { Loadanh(des, "nhanvat//kright.png"); }

		else if (status == Walk_up) { Loadanh(des, "nhanvat//kup.png"); }

		else
		{
			Loadanh(des, "nhanvat//kdown.png");
		}

		if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1)
		{
			trangthai++;
		}
		else if (trangthai > 6) trangthai = 0;
		else trangthai = 0;

		rect_.x = x_pos - MAPP_X;
		rect_.y = y_pos - MAPP_Y;

		SDL_Rect* current_clip = &Frame2_kiem_[trangthai];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame,height_frame };

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}

	//cout << trangthai << '\n';
	
}


void playermain::button(SDL_Event event, SDL_Renderer* screen)
{

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			status = Walk_right;
			input_type.right = 1;
			break;
		case SDLK_LEFT:
			status = Walk_left;
			input_type.left = 1;
			break;
		case SDLK_UP:
			status = Walk_up;
			input_type.up = 1;
			break;
		case SDLK_DOWN:
			status = Walk_down;
			input_type.down = 1;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			input_type.right = 0;
			break;
		case SDLK_LEFT:
			input_type.left = 0;
			break;
		case SDLK_UP:
			input_type.up = 0;
			break;
		case SDLK_DOWN:
			input_type.down = 0;
			break;
		default:
			break;
		}
	}
	//cout << input_type.right << " " << input_type.left << " " << input_type.up << " " << input_type.down << '\n';

}


void playermain::nhanvatdichuyen(Map& map_data)
{
	x_val = 0;
	y_val = 0;

	if (input_type.left == 1) {
		x_val -= speed_player;
	}
	else if (input_type.right == 1) {
		x_val += speed_player;
	}
	else if (input_type.up == 1) {
		y_val -= speed_player;
	}
	else if (input_type.down == 1) {
		y_val += speed_player;
	}
	checkvachammap(map_data);
	Setthongsomap(map_data);
}

void playermain::Setthongsomap(Map& map_data)
{
	map_data.start_x_ = x_pos - (screen_chieudai / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + screen_chieudai >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_- screen_chieudai;
	}

	map_data.start_y_ = y_pos - (screen_chieurong / 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;		
	}

	else if (map_data.start_y_ + screen_chieurong    >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_- screen_chieurong;
	}
}



 int playermain::checkomap(const int &x, const int &y, Map& map_data)
{
	 if (map_data.F[x][y] != 0 && map_data.F[x][y] != 2 && map_data.F[x][y] != 3 && map_data.F[x][y] != 4 && map_data.F[x][y] != 5)
	 {
		 return 1;
	 }

	 else if (map_data.F[x][y] == 2) return 2;
	 else if (map_data.F[x][y] == 3) return 3;
	 else if (map_data.F[x][y] == 4) return 4;
	 else if (map_data.F[x][y] == 5) return 5;

}
void playermain::checkvachammap(Map& map_data)
{
	int x1, x2, y1, y2;
	x1 = x2 = y1 = y2 = 0;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame / 2) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame / 2) / TILE_SIZE;

	if (x1 >= 0 && x2 < Map_x && y1 >= 0 && y2 < Map_y)
	{
		// Kiểm tra va chạm ở phía trên và dưới
		if (checkomap(y1, x1, map_data) == 0 && checkomap(y2, x2,map_data) == 0) status_chiendau = 0;
		if (checkomap(y1, x1, map_data) == 2 || checkomap(y2, x2, map_data) == 2) status_chiendau = 1;
		if (checkomap(y1, x1, map_data) == 3 || checkomap(y2, x2, map_data) == 3) status_chiendau = 2;

		 if(checkomap(y1-1,x1,map_data)==1 && checkomap(y1-1,x2,map_data)==1)
		{
			// Nếu gặp chướng ngại vật ở phía trên, dừng lại và đặt nhân vật ở ô dưới chướng ngại vật
			y_pos = y1 * TILE_SIZE;
			y_val = 0;
		}
		else  if(checkomap(y2+1,x1,map_data)==1 && checkomap(y2+1,x2,map_data)==1)
		 {
			// Nếu gặp chướng ngại vật ở phía dưới, dừng lại và đặt nhân vật ở ô phía trên chướng ngại vật
			y_pos = (y2 + 1) * TILE_SIZE - height_frame;
			y_val = 0;
		}

		// Kiểm tra va chạm ở phía trái và phải
		 if(checkomap(y1,x1-1,map_data)==1 && checkomap(y2,x1-1,map_data)==1)
		{
			// Nếu gặp chướng ngại vật ở phía trái, dừng lại v     à đặt nhân vật ở ô bên phải chướng ngại vật
			x_pos = (x1 + 1) * TILE_SIZE;
			x_val = 0;
		}
		else if(checkomap(y1,x2+1,map_data)==1 && checkomap(y2,x2+1,map_data)==1)
		{
			// Nếu gặp chướng ngại vật ở phía phải, dừng lại và đặt nhân vật ở ô bên trái chướng ngại vật
			x_pos = x2 * TILE_SIZE - width_frame;
			x_val = 0;
		}

	}

	x_pos += x_val;
	y_pos += y_val;
}



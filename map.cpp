#include "map.h"
#include <cstdio> // Để sử dụng fopen_s và fscanf_s

void GameMap::loadmap(char* name)
{
	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, name, "rb");

	if (err != 0 || fp == NULL) {
		// Xử lý lỗi mở tập tin
		return;
	}

	gamemap.max_x_ = 0;
	gamemap.max_y_ = 0;

	for (int i = 0; i < Map_y; i++)
	{
		for (int j = 0; j < Map_x; j++)
		{
			fscanf_s(fp, "%d", &gamemap.F[i][j]);

			// Sử dụng chỉ mục trực tiếp trong mảng F
			int val = gamemap.F[i][j];
			//cout << gamemap.F[i][j] ;

			if (val > 0)
			{
				if (j > gamemap.max_x_) gamemap.max_x_ = j;
				if (i > gamemap.max_y_) gamemap.max_y_ = i;
			}
		}
		//cout << '\n';
	}

	gamemap.max_x_ = (gamemap.max_x_ + 1) * TILE_SIZE;
	gamemap.max_y_ = (gamemap.max_y_ + 1) * TILE_SIZE;
	gamemap.start_x_ = 0;
	gamemap.start_y_ = 0;

	gamemap.file_name = name;
	fclose(fp);
}


void GameMap::loadtile(SDL_Renderer* screen)
{
	char file_img[30];

	FILE* fp = NULL;
	for (int i = 0; i < max_tile; i++)
	{
		sprintf_s(file_img, "bando/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);

		tile_map[i].Loadanh(screen,file_img);
	}
}


void GameMap::Drawmap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//gamemap.max_x_ = 0;
	//gamemap.max_y_ = 0;

	int map_x = gamemap.start_x_ / TILE_SIZE;
    int map_y = gamemap.start_y_ / TILE_SIZE;

   x1 = (gamemap.start_x_ % TILE_SIZE) * -1;
   y1 = (gamemap.start_y_ % TILE_SIZE) * -1;
   //x1 = 0; y1 = 0;


x2 = x1 + screen_chieudai + (x1 == 0 ? 0 : TILE_SIZE);
y2 = y1 + screen_chieurong + (y1 == 0 ? 0 : TILE_SIZE); 
//cout << '\n' << x1<<" "<<x2;
//x2 = 1200; y2 = 600;

for (int i = y1; i < y2; i += TILE_SIZE)
{		map_x = gamemap.start_x_ / TILE_SIZE;

	for (int j = x1; j < x2; j += TILE_SIZE)
	{
		int val = gamemap.F[map_y][map_x];
		//cout << map_x <<res<< " ";
		if (val > 0)
		{
			tile_map[val].setrect(j, i);
			tile_map[val].Render(screen);
		}
		map_x++;
		//if (map_x >= Map_x) break; // Đảm bảo rằng không vượt quá phạm vi của bản đồ
	}
	
	map_y++;
	//cout << '\n';
	//if (map_y >= Map_y) break; // Đảm bảo rằng không vượt quá phạm vi của bản đồ
}

}


#include "base.h"

base::base()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

base::~base()
{
	Free();
}

bool base::Loadanh(SDL_Renderer* screen,string path)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());

	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, color_R, color_G, color_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);


		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;

		}
		SDL_FreeSurface(load_surface);

	}

	p_object_ = new_texture;
	
	if (p_object_ != NULL) return true;
	return false;
}


void base::Render(SDL_Renderer* des, const SDL_Rect* clip)
	{
	SDL_Rect renderquad = { rect_.x, rect_.y,rect_.w,rect_.h };
	SDL_RenderCopy(des, p_object_, clip, &renderquad);

	}

void base::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}

void base::docmap(string filename)
{
	ifstream file(filename);

	map.resize(2000);
	for (int i = 0; i < 2000; i++) map[i].resize(2000);

	if (file.is_open())
		{
			for (int y = 0; y < 2000; ++y) {
				for (int x = 0; x < 2000; ++x) {
					file >> map[y][x]; // Đọc giá trị từ file vào map
				}
			}
			file.close();
		}
}

void base::veanh()
{
	
}

void base::taomap()
{

}
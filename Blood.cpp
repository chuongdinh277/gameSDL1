#include "Blood.h"

void BLOOD:: RenderRectangle(const BloodFormat& geo_size, const ColorData& color_data, SDL_Renderer* renderer)
{
	SDL_Rect fill_rect = { geo_size.left_,geo_size.top_,geo_size.width_,geo_size.height_ };
	//SDL_GetRenderDrawColor(renderer, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
	SDL_SetRenderDrawColor(renderer, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
	SDL_RenderFillRect(renderer, &fill_rect);
}

void BLOOD:: RenderOutline(const BloodFormat& geo_size, const ColorData& color_data, SDL_Renderer* renderer)
{
	SDL_Rect out_rect = { geo_size.left_,geo_size.top_,geo_size.width_,geo_size.height_ };

	SDL_SetRenderDrawColor(renderer, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
	SDL_RenderDrawRect(renderer, &out_rect);

}
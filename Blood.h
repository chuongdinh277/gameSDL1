#pragma once
#ifndef BLODD_H
#define BLOOD_H

#include "foundation.h"


#define blood_max 500


// tạo thanh máu
typedef struct BloodFormat
{
public: 
	BloodFormat(int left, int top, int width, int height) { left_ = left, top_ = top, width_ = width, height_ = height; };
	int left_;
	int top_;
	int width_;
	int height_;
};
typedef struct ColorData
{
	ColorData(Uint8 r, Uint8 g, Uint8 b) { red_ = r, green_ = g, blue_ = b;}
public:
	
	Uint8 red_;
	Uint8 green_;
	Uint8 blue_;
};
class BLOOD
{
public: 
	static void RenderRectangle(const BloodFormat& geo_size, const ColorData& color_data, SDL_Renderer* renderer);
	static void RenderOutline(const BloodFormat& geo_size, const ColorData& color_data, SDL_Renderer* renderer);

};
#endif 

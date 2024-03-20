

#ifndef map_H_
#define map_H_

#include "Chung.h"
#include "base.h"


const int max_tile = 20;

class tilemap : public base
{
public:
	tilemap() { ; }
	~tilemap() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void loadmap(char* name);

	void loadtile(SDL_Renderer* screen);
	void Drawmap(SDL_Renderer* screen);

	Map getmap() const { return gamemap; };
	void setmap(Map& map_data)
	{
		gamemap = map_data;
	};


private:
	Map gamemap;
	tilemap tile_map[max_tile];
};

#endif map_H_

#ifndef base_H_
#define base_H_

#include "Chung.h"

class base
{
public:
	base();
	~base();
	void setrect(const int& x, const int& y)
	{
		rect_.x = x;
		rect_.y = y;
	}

	SDL_Rect GetRect() const { return rect_ ; }

	SDL_Texture* GetObject() const{ return p_object_; }

	virtual bool Loadanh(SDL_Renderer* screen, string path );

	void Render(SDL_Renderer* des, const SDL_Rect* clipp = NULL);

	void Free();


	void docmap(string filename);

	void taomap();
	void veanh();


protected:

	SDL_Texture* p_object_;
	SDL_Rect rect_;

};



#endif //base_h_


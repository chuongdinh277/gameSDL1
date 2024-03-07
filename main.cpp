
#include  "chung.h" 
#include "base.h"

BaseObject g_background;



void close()
{
    g_background.free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }

    g_window = SDL_CreateWindow("GameSDL", 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_SHOWN);


    if (g_window == NULL) success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
        }
    }
     
    return success;  
}

bool loadBackground()
{
    bool ret = g_background.LoadImg(g_screen, "bg2.png");
    if (ret == false) return false;
    return true;
}


int main(int argc, char* argv[])
{
      
    if (InitData() == false)
    {
        return -1;
    }

    if (loadBackground() == false)
        return -1;

    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT) is_quit = true;
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);


        g_background.Render(g_screen, NULL);
         
        SDL_RenderPresent(g_screen);

    }

    close();
    return 0;

}  


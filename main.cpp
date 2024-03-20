
#include "chung.h" 
#include "base.h"
#include "map.h"
#include"playermain.h"

base g_background;



void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;
   // SDL_DestroyTexture(treeTexture);
    //treTexture = NULL;

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
        screen_chieudai, screen_chieurong,
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
    bool ret = g_background.Loadanh(g_screen, "background/anhnen.jpg");
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


    GameMap game_map;
    game_map.loadmap(const_cast<char*>("bando/map.txt"));
    game_map.loadtile(g_screen);



    playermain p_player;
    p_player.Loadanh(g_screen, "nhanvat//right.png");
    p_player.set_clip();





 while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT) is_quit = true;

            p_player.button(g_event, g_screen);

        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);
         
        g_background.Render(g_screen, NULL);

       // game_map.Drawmap(g_screen);

        Map map_data = game_map.getmap();

        
        
        p_player.Setmaptheonhanvat(map_data.start_x_, map_data.start_y_);
            
        p_player.nhanvatdichuyen(map_data);
        p_player.Show(g_screen);

        game_map.setmap(map_data);
       game_map.Drawmap(g_screen);

        
        SDL_RenderPresent(g_screen);

    }

    close();
    return 0;

}

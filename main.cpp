
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "audio.h"
#include "foundation.h"
#include "map.h"
#include "menu.h"
#include "perks.h"
#include "player.h"
#include "boss.h"
#include "Time.h"
#include "Blood.h"
#include <vector>

int main(int argc, char** argv) 
{
    //khoi tao game
    int Val_Perk = 0;
    std::srand(time(NULL));
    int timeAtLoopBeginning;
    bool Bom_start = false;
    bool Bom_endl = false;
    FRAMEWORK game = { NULL, NULL, NULL, 0, NULL, false, false, false , false, false, false, false ,false };
    Background resources;
    Player player = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    Timer timerData = { 0, 0, -1, -1 };
    
    Time_delay time_delay_start;
    Time_delay time_delay_end;
    time_delay_start.Start();
    time_delay_end.Start();
    
    INITIALIZE(&game);
    initiateMapResources(game.renderer, &resources);

    Camera camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
   
    //khoi tao boss
    std::vector<Boss> monsters(101);
    for (int i = 0; i < 100; i++)
    {
         render_boss(game, monsters[i]);
        boss_Move(monsters[i], camera);
    }
    std::vector<Perk> perk(60);

    BOM bom;
    int playerNUMBER=-1;
    bool ok = true;
    //sinh boss
    for (int i = 0; i <100; i++)
    {
        monsters[i].kt = true;
        monsters[i].check = true;
        int x = rand() % 2000; 
        int y = rand() % 2000;
        //x = 32; y = 64;
        Random(monsters[i],x,y);
    }
    //Random(monster, rand() % 20, rand() % 20);
    for (int i = 0; i < 60; i++) perk[i].cc = rand() % 3+1;
    for (int i = 0; i <60; i++)
    {
            perk[i].check = true;
            int x = rand() % 1500;
            int y = rand() % 1500;
            random_perk(perk[i], x, y);
    }

    while (!game.QUIT) 
    {
        timeAtLoopBeginning = SDL_GetTicks();
        if (game.MENU_STATE)
        {
            player = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            player.position.x = 840; 
            player.position.y = 450;
            player.GameOver = true;
            player.blood = blood_max;
            game.GAMEOVER = false;
            camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            playerNUMBER = manageMenu(&game, player) ;
            Val_Perk = 0;
            ok = true;
            timerData.TIME_START = time(NULL);

            for (int i = 0; i < 60; i++) perk[i].cc = rand() % 3 + 1;
            for (int i = 0; i < 60; i++)
            {
                perk[i].check = true;
                int x = rand() % 1500;
                int y = rand() % 1500;
                random_perk(perk[i], x, y);
            }
            time_delay_start.Start();
            time_delay_end.Start();
            Bom_start = false;
            Bom_endl = false;
        }
        else 
        {
            renderBackground(&game, resources, &camera);
            if (player.blood >= blood_max) player.blood = blood_max;
            BloodFormat rectangle_size(10, 10, player.blood, 40);
            ColorData color_data(0, 80, 150);
            BLOOD::RenderRectangle(rectangle_size, color_data, game.renderer);
            BloodFormat outlineSize(12, 12, blood_max- 1, 38);
            ColorData color_data2(255, 255, 255);
            BLOOD::RenderOutline(outlineSize, color_data2, game.renderer);
            //Boss
            
               for (int i = 0; i < 100; i++)
                 {
                     boss_Move(monsters[i], camera);
                 }
               for (int i = 0; i < 60; i++)
               {
                   perk_movie(perk[i], camera);
               }
           player= loadPlayers(game.renderer, player, playerNUMBER,player.position.x,player.position.y);
            Bom_movie(bom, camera);
            handleInput(&game, player, camera, bom); 
            Move_Player(player, camera,game.renderer);
            if (player.boom == true)
            {
                if (Bom_start)  time_delay_start.Start();
                Bom_movie(bom, camera);
               
                Render_Bom(game.renderer, bom);
                SDL_DestroyTexture(bom.bom_texture);
                Bom_start = false; Bom_endl = true;
            }
            else Bom_start = true;
     
            if (time_delay_start.gettick() > 1000)
            {
                player.boom = false;
                if(Bom_endl) time_delay_end.Start();
                Bom_endl = false;
            }
            if (time_delay_end.gettick() < 1000)
            {
                for (int i = 0; i < 100; i++)
                {
                    int x = bom.position_bomno.x;
                    int y = bom.position_bomno.y;

                    int u = monsters[i].position.x;
                    int v = monsters[i].position.y;

                    int res = max(abs(u - x), abs(v - y));

                    if (res <= 80)
                    {
                        monsters[i].position = { 0,0,0,0 };
                        monsters[i].kt = false;
                        monsters[i].check = false;
                        SDL_DestroyTexture(monsters[i].monster_texture);
                        // monsters.erase(monsters.begin() + i);
                    }
                }
                Render_bumbum(game.renderer, bom); player.bum_bum_no = true;

            }
            else player.bum_bum_no = false;
            //cout << player.speed << '\n';
            Val_Perk = 0;
            for(int i=0;i<100;i++) Find_hunter(monsters[i], player, &game);
            for (int i = 0; i < 60; i++)
            {
                if (perk[i].check) {
                    renderPerk(game.renderer, &perk[i], player, &camera, perk[i].cc);
                }
                else Val_Perk++;

            }
            SDL_Color color = { 255, 255, 255 };
            std::string s = "Number of perk to collect: " + std::to_string(30 - Val_Perk);
            SDL_Surface* valOptionSurface = TTF_RenderText_Solid(game.font, s.c_str(), color);
            SDL_Texture* valOptionTexture = SDL_CreateTextureFromSurface(game.renderer, valOptionSurface);
            SDL_Rect valOptionRect = { 700, 10, valOptionSurface->w, valOptionSurface->h }; 
            SDL_Rect backgroundRect = { 695, 9, valOptionSurface->w + 5, valOptionSurface->h+ 5 };
            SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(game.renderer, &backgroundRect);
            SDL_RenderCopy(game.renderer, valOptionTexture, NULL, &valOptionRect);
            SDL_DestroyTexture(valOptionTexture);
            SDL_FreeSurface(valOptionSurface);
            if (player.blood <= 0)
            {
                game.GAMEOVER = true; game.Win = false;
            }
            else if (Val_Perk == 30)
            {
                game.Win = true; game.GAMEOVER = false;
            }
            else if (timerData.MINUTE_REMAIN == 0 && timerData.SECOND_REMAIN == 0)
            {
                game.GAMEOVER = true;
            } 
            DISPLAY_GAMEOVER(&game, &timerData);
            SDL_DestroyTexture(player.spriteSheetTexture);
            manageTimer(&game, &timerData);
            SDL_RenderPresent(game.renderer);
            MANAGE_FRAME(timeAtLoopBeginning);
        }
    }
    SDL_DestroyWindow(game.window);
    TTF_CloseFont(game.font);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
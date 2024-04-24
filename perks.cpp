#include "perk.h"

void random_perk(Perk& perk, int x, int y)
{
    perk.x_pos = x;
    perk.y_pos = y;
    perk.rect.w = PERK_WIDTH;
    perk.rect.h = PERK_HEIGHT;

}

void renderPerk(SDL_Renderer* renderer, Perk* perk, Player& player, Camera* camera, int sc) 
{
    if (sc == 1) {
        perk->cc = 1; 
        perk->texture = IMG_LoadTexture(renderer, "resources/perk_1.png");
    }
    else if (sc == 2) {
        perk->cc = 2;
        perk->texture = IMG_LoadTexture(renderer, "resources/perk_2.png");
    }
    else if (sc == 3) {
        perk->cc = 3;
        perk->texture = IMG_LoadTexture(renderer, "resources/perk_3.png");
    }

        int playerX = player.position.x + camera->x;
        int playerY = player.position.y + camera->y;
       // perk->rect.x = perk->x_pos - camera->x;
        //perk->rect.y = perk->y_pos - camera->y;
        int perkX = perk->rect.x + camera->x;
        int perkY = perk->rect.y + camera->y;
        int d = sqrt((playerX - perkX) * (playerX - perkX) + (playerY - perkY) * (playerY - perkY));
        //
        if (d<20)
        {
           // cout << playerX << " " << playerY << " asa " << perkX << " " << perkY << '\n';
            perk->check = false;
            player.hasPerk += 1;
            if (sc == 1) player.blood += 25;
            else if (sc == 2) {
                player.speed = 2*Default_Speed; player.end_speed = player.start_speed + 5000;
            }
            else if (sc == 3) {
                player.end_blood = player.start_blood + 5000;
            }
        }
        else perk->check = true;
        if(perk->check==true) SDL_RenderCopy(renderer, perk->texture, NULL, &perk->rect);
        SDL_DestroyTexture(perk->texture);
}


void perk_movie(Perk& perk, Camera camera)
{
    perk.rect.x = perk.x_pos - camera.x;
    perk.rect.y = perk.y_pos - camera.y;
}

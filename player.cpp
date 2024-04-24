#include "player.h"
#include <string>
#include "map.h"
#include "foundation.h"
#include "boss.h"

static Player createPlayer(SDL_Renderer* renderer, string playerModel, int positionX, int positionY,Player &playerX) {
   

     playerX.spriteSheetTexture = IMG_LoadTexture(renderer, playerModel.c_str());
    if (playerX.spriteSheetTexture == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    int frame_count = 0;
    for (int y = 0; y < 4; y++) 
    {
        for (int x = 0; x < 3; x++) 
        {
            playerX.spriteClip[frame_count].x = x * (PLAYER_FRAME_HEIGHT)+1;
            playerX.spriteClip[frame_count].y = y * (PLAYER_FRAME_WIDTH)+3;
            playerX.spriteClip[frame_count].w = PLAYER_FRAME_WIDTH;
            playerX.spriteClip[frame_count].h = PLAYER_FRAME_HEIGHT;
            frame_count++;
        }
    }

    

    playerX.position.x = positionX;
    playerX.position.y = positionY;
    playerX.position.w = PLAYER_FRAME_WIDTH;
    playerX.position.h = PLAYER_FRAME_HEIGHT;

    //playerX.frame = 0;
    if(playerX.speed==0) playerX.speed = Default_Speed;
    playerX.captured = false;
    playerX.movementKeysReversed = false;
    return playerX;
}
void renderPlayers(FRAMEWORK game, Player players) 
{
        SDL_Rect playerPosition = players.position;
        SDL_RenderCopyEx(game.renderer, players.spriteSheetTexture, &players.spriteClip[players.frame], &playerPosition, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(players.spriteSheetTexture);

}

Player loadPlayers(SDL_Renderer* renderer, Player players , int PLAYER_NUMBER,int x_pos,int y_pos) 
{
   
    if (PLAYER_NUMBER == 0) players = createPlayer(renderer, "resources/Runner_1.png", x_pos, y_pos, players);
    if (PLAYER_NUMBER == 1) players = createPlayer(renderer, "resources/Hunter.png", x_pos, y_pos,players);
    if (PLAYER_NUMBER == 2) players = createPlayer(renderer, "resources/Runner_2.png", x_pos, y_pos,players);
    if (PLAYER_NUMBER == 3) players = createPlayer(renderer, "resources/Runner_3.png", x_pos, y_pos,players);
    if (PLAYER_NUMBER == 4) players = createPlayer(renderer, "resources/Hunter_2.png", x_pos, y_pos,players);
    return players;
}
void handleInput(FRAMEWORK* game, Player &player, Camera &camera, BOM &bom)
{
    BOM BOOM;
    int frame_count = player.frame;
    while (SDL_PollEvent(&game->event))
    {
            if (player.GameOver == false) break;
            if (game->event.type == SDL_KEYDOWN)
            {
                switch (game->event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                {
                    if (player.right == false) frame_count = 6;
                    player.right = true;
                    player.down = false;
                    player.up = false;
                    player.left = false;

                    break;
                }
                case SDLK_LEFT:
                {
                    if (player.left == false) frame_count = 3;
                    player.left = true;
                    player.right = false;
                    player.up = false;
                    player.down = false;
                    break;
                }
                case SDLK_UP:
                {
                    if (player.up == false) frame_count = 9;
                    player.left = false;
                    player.right = false;
                    player.up = true;
                    player.down = false;
                    break;
                }
                case SDLK_DOWN:
                {
                    if (player.down == false) frame_count = 0;
                    player.left = false;
                    player.right = false;
                    player.up = false;
                    player.down = true;
                    break;
                }
                case SDLK_s:
                {
                    if (player.boom == false&&player.bum_bum_no==false) {
                        player.boom = true;
                        player.left = false;
                        player.right = false;
                        player.up = false;
                        player.down = false;
                        bom.x_pos = camera.x + player.position.x;
                        bom.y_pos = camera.y + player.position.y;
                    }
                    break;
                }

                default:
                    player.No = true;
                    break;
                }
            }
                if (game->event.type == SDL_KEYUP) {
                    switch (game->event.key.keysym.sym) {
                    case SDLK_UP: player.up = false;
                        break;
                    case SDLK_DOWN: player.down = false;
                        break;
                    case SDLK_RIGHT: player.right = false;
                        break;
                    case SDLK_LEFT: player.left = false;
                        break;
                    }
                }
    }
    player.No = false;
}
void Move_Player(Player& player,Camera &camera,SDL_Renderer* renderer) {
    int frame_count = player.frame;
    player.start_speed = SDL_GetTicks();
    player.start_blood = SDL_GetTicks();
    if (player.No == false)
    {
        checkMap(camera, player);
        if (player.right == true)
        {
            frame_count++;
            if ((camera.x >= 2752 - SCREEN_WIDTH || player.position.x <= 420)) player.position.x += player.speed;
            if (player.position.x >= 420) camera.x += player.speed;
        }
        else if (player.left == true)
        {
            frame_count++;
            if (camera.x == 0 || camera.x == 2752 - SCREEN_WIDTH) player.position.x -= player.speed;
            if (player.position.x <= SCREEN_WIDTH * 2 / 3)   camera.x -= player.speed;
        }
        else if (player.up == true)
        {
            frame_count++;
            if (camera.y == 0 || camera.y == 1536 - SCREEN_HEIGHT) player.position.y -= player.speed;
            if (player.position.y <= SCREEN_HEIGHT * 2 / 3) camera.y -= player.speed;
        }
        else if (player.down == true)
        {
            frame_count++;
            if (camera.y >= 1536 - SCREEN_HEIGHT || player.position.y <= 420)  player.position.y += player.speed;
            if (player.position.y >= 420)  camera.y += player.speed;
        }

    }
    if (player.right == true) {
        if (frame_count >= 9) frame_count = 6;
    }
    else if (player.left == true) {
        if (frame_count >= 6) frame_count = 3;
    }
    else   if (player.up == true) {
        if (frame_count >= 12) frame_count = 9;
    }
    else  if (player.down == true) {
        if (frame_count >= 3) frame_count = 0;
    }
    if (player.right == true && frame_count == -1) frame_count = 6;
    else if (frame_count == -1 && player.left == true) frame_count = 3;

    if (camera.x < 0) camera.x = 0;
    else if (camera.y < 0) camera.y = 0;

    if (camera.x > 2752 - SCREEN_WIDTH && player.position.x > SCREEN_WIDTH * 2 / 3) camera.x = 2752 - SCREEN_WIDTH;
    if (camera.y > 1536 - SCREEN_HEIGHT) camera.y = 1536 - SCREEN_HEIGHT;
    if (player.position.x > SCREEN_WIDTH * 2 / 3 && camera.x < 2752 - SCREEN_WIDTH)
    {
        //camera.x = 2752 - SCREEN_WIDTH;
        player.position.x = SCREEN_WIDTH * 2 / 3;
    }
    else if (player.position.x < SCREEN_WIDTH * 1 / 3 && camera.x > 0)
    {
        player.position.x = SCREEN_WIDTH * 1 / 3;
    }

    if (player.position.y > SCREEN_HEIGHT * 2 / 3 && camera.y < 1536 - SCREEN_HEIGHT) player.position.y = SCREEN_HEIGHT * 1 / 3;
    else if (player.position.y < SCREEN_HEIGHT * 1 / 3 && camera.y >0)  player.position.y = SCREEN_HEIGHT * 2 / 3;
    Camera map = camera;
    SDL_Rect viewPoint = { map.x, map.y, map.width, map.height };

    SDL_RenderCopy(renderer, player.spriteSheetTexture, &player.spriteClip[frame_count], &player.position);

    player.frame = frame_count;
    if (player.start_speed >= player.end_speed) {
        player.speed = Default_Speed;
    }
    if (player.start_blood <= player.end_blood) {
        player.battu = true;
    }
    else player.battu = false;
}
void checkMap(Camera& camera, Player& player)
{
    int x = (player.position.x + camera.x) ;
    int y= (player.position.y + camera.y) ;
    int kt;
    kt = checktieMap(y, x);
    if (kt == 1) player.blood -= 3;
    if (player.left == true)
    {
        if (x/32 - 1 < 0 ) player.speed = 0;
        else if(player.speed ==0) player.speed = Default_Speed;
    }
    
    else if (player.right == true)
    {
        if (x/32 + 1 > 84 )  player.speed = 0;
        else if(player.speed ==0) player.speed = Default_Speed;

    }
    else if (player.up == true)
    {
       if (y/32 - 1 < 0 ) player.speed = 0;
       else if(player.speed ==0 )  player.speed = Default_Speed;
    }
    else if (player.down == true)
    {
        if (y/32 + 1 > 46 ) player.speed = 0;
        else if(player.speed == 0)  player.speed = Default_Speed;
    }

}
int checktieMap(int y, int x)
{
    for (int i = 0; i < MAP_COLUMNS; i++)
    {
        for (int j = 0; j < MAP_ROWS; j++)
        {
            int y1 = i * 32;
            int x1 = j * 32;

            if (abs(x1 - x) <= 20 && abs(y1 - y) <= 20 )
            {
                if (mapGrid[i][j] >= 63 && mapGrid[i][j] <= 94) return 1;
                if (mapGrid[i][j] >= 27 && mapGrid[i][j] <= 44) return 1;
            }
        }
   }
    return 2;
}
void Render_Bom(SDL_Renderer* renderer, BOM &bom)
{
    bom.bom_texture = IMG_LoadTexture(renderer,"resources/boom.png");
    bom.position.w = 32;
    bom.position.h = 32;

    //player.boom = false;
   SDL_RenderCopy(renderer, bom.bom_texture, NULL, &bom.position);
}
void Bom_movie(BOM& bom, Camera camera)
{
    bom.position.x = bom.x_pos - camera.x ;
    bom.position.y = bom.y_pos - camera.y;
}
void Render_bumbum(SDL_Renderer* renderer, BOM& bom)
{
    bom.Bom_Bom = IMG_LoadTexture(renderer, "resources/bomno.png");

    SDL_Rect bombum;
    bombum = bom.position;
    bombum.x -= 30;
    bombum.y -= 35;
    bombum.h = 150;
    bombum.w = 150;
    bom.position_bomno = bombum;
    SDL_RenderCopy(renderer, bom.Bom_Bom, NULL, &bombum);
    SDL_DestroyTexture(bom.Bom_Bom);
}

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
    playerX.speed = Default_Speed;
    // playerX.speedBoostStartTime = 0;
    // playerX.baseSpeed = 2;
    // playerX.boostedSpeed = 4;

   // playerX.player = playerNumber;
    playerX.captured = false;
    playerX.movementKeysReversed = false;
    return playerX;
}
void renderPlayers(FRAMEWORK game, Player players) 
{
        SDL_Rect playerPosition = players.position;
        //cout << " " << camera.x << " " << camera.y << '\n';
        SDL_RenderCopyEx(game.renderer, players.spriteSheetTexture, &players.spriteClip[players.frame], &playerPosition, 0, NULL, SDL_FLIP_NONE);

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
                if(player.right==false) frame_count = 6;
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
                if (player.boom == false) {
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
            if (player.No == false)
            {

                checkMap(camera, player);
               // cout << player.speed << '\n';
                if (player.right == true)
                {
                    frame_count++;
                    if((camera.x>=2752-SCREEN_WIDTH|| player.position.x <=420 )) player.position.x += player.speed;
                    if(player.position.x>=420) camera.x += player.speed;
                }
                else if (player.left == true)
                {
                    frame_count++;
                    if(camera.x==0 || camera.x == 2752-SCREEN_WIDTH) player.position.x -= player.speed; 
                    if(player.position.x <= SCREEN_WIDTH*2/3)   camera.x -= player.speed;
                }
                else if (player.up == true)
                {
                    frame_count++;
                    if(camera.y==0 || camera.y == 1536- SCREEN_HEIGHT) player.position.y -= player.speed;
                    if(player.position.y <= SCREEN_HEIGHT*2/3) camera.y -= player.speed;
                }
                else if (player.down == true)
                {
                    frame_count++;
                    if(camera.y>=1536-SCREEN_HEIGHT || player.position.y <= 420)  player.position.y += player.speed; 
                    if(player.position.y >=420)  camera.y += player.speed;
                }

                
                

            }
        }
        
        //SDL_Rect player_position = player.position;
        //cout << frame_count << '\n';
        //SDL_RenderCopyEx(game->renderer, player.spriteSheetTexture, &player.spriteClip[frame_count], &player_position, 0, NULL, SDL_FLIP_NONE);
    }

    if (player.boom == true)
    {
        //Render_Bom(game->renderer, BOOM);
        //BOOM.position.x = player.position.x;
        //BOOM.position.y = player.position.y;
       // BOOM.position.w = 32;
       // BOOM.position.h = 32;
        //player.boom = false;
        
        //SDL_RenderCopy(game->renderer, BOOM.bom_texture, NULL, &BOOM.position);
        //SDL_RenderPresent(game->renderer);

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
    //else if (frame_count == -1) frame_count = 0;
   
    if (camera.x < 0) camera.x = 0;
    else if (camera.y < 0) camera.y = 0;

    if (camera.x > 2752 - SCREEN_WIDTH && player.position.x > SCREEN_WIDTH *2/3) camera.x = 2752 - SCREEN_WIDTH ;
    if (camera.y > 1536 - SCREEN_HEIGHT) camera.y = 1536 - SCREEN_HEIGHT;

    //cout << camera.x << " " << camera.y << '\n';
    if (player.position.x > SCREEN_WIDTH * 2 / 3 && camera.x < 2752 - SCREEN_WIDTH)
    {
        //camera.x = 2752 - SCREEN_WIDTH;
        player.position.x = SCREEN_WIDTH * 2 / 3; 
    }
    else if (player.position.x < SCREEN_WIDTH * 1 / 3 && camera.x > 0) 
    { 
        player.position.x = SCREEN_WIDTH * 1 / 3; }

    if (player.position.y > SCREEN_HEIGHT * 2 / 3 && camera.y <1536 -SCREEN_HEIGHT) player.position.y = SCREEN_HEIGHT * 1 / 3;
   else if (player.position.y < SCREEN_HEIGHT * 1 / 3 && camera.y >0)  player.position.y = SCREEN_HEIGHT * 2 / 3;
   // getMap(camera, player);
    Camera map = camera;
    //cout << player.position.x << " " << player.position.y<<'\n';
    SDL_Rect viewPoint = { map.x, map.y, map.width, map.height };
    //SDL_RenderSetViewport(game->renderer, &viewPoint);  
    //cout << player.speed << " ";
    
    // SDL_RenderCopy(game->renderer, BOOM.bom_texture,NULL,  &BOOM.position);
    SDL_RenderCopy(game->renderer, player.spriteSheetTexture, &player.spriteClip[frame_count], &player.position);
   
    player.frame = frame_count;
    player.No = false;
}
void checkMap(Camera& camera, Player& player)
{
    int x = player.position.x/32 + camera.x/32;
    int y = player.position.y/32 + camera.y/32;
    cout << y << " " << x << " " << mapGrid[y][x]<<'\n';
    int kt;
    if (player.left == true)
    {
        
        kt = checktieMap(y, x);
        if (kt==1) player.GameOver = false;
        if (x - 1 < 0 ) player.speed = 0;
        else player.speed = Default_Speed;
    }
    
    else if (player.right == true)
    {
        //cout << 1 << " ";
        
        kt = checktieMap(y, x);
        if (kt ==1) player.GameOver = false;
        if (x + 1 > 84 )  player.speed = 0;
        else player.speed = Default_Speed;

    }
    else if (player.up == true)
    {
        
       kt = checktieMap(y, x);
       if (kt ==1) player.GameOver = false;
       if (y - 1 < 0 ) player.speed = 0;
       else player.speed = Default_Speed;
    }
    else if (player.down == true)
    {
        
        kt = checktieMap(y, x);
        if (kt==1) player.GameOver = false;
        if (y + 1 > 46 ) player.speed = 0;
        else player.speed = Default_Speed;
    }

}
int checktieMap(int y, int x)
{
    if (mapGrid[y][x] >= 1 && mapGrid[y][x] <= 3) return 4;
    else if (mapGrid[y][x] >= 7 && mapGrid[y][x] <= 9) return 4;
    else if (mapGrid[y][x] >= 10 && mapGrid[y][x] <= 12) return 4;
    else if (mapGrid[y][x] >= 16 && mapGrid[y][x] <= 18) return 4;
    else if (mapGrid[y][x] >= 19 && mapGrid[y][x] <= 21) return 4;
    else if (mapGrid[y][x] >= 25 && mapGrid[y][x] <= 27) return 4;
    else if (mapGrid[y][x] >= 46 && mapGrid[y][x] <= 48) return 4;
    else if (mapGrid[y][x] >= 52 && mapGrid[y][x] <= 54) return 4;
    else if (mapGrid[y][x] >= 55 && mapGrid[y][x] <= 57) return 4;
    else if (mapGrid[y][x] >= 61 && mapGrid[y][x] <= 63) return 4;
    else if (mapGrid[y][x] >= 10 && mapGrid[y][x] <= 12) return 4;
    else if (mapGrid[y][x] >= 97 && mapGrid[y][x] <= 99) return 4;

    else if (mapGrid[y][x] >= 64 && mapGrid[y][x] <= 90) return 1;
    else return 2;
     
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
}

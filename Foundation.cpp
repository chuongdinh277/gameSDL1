#include "foundation.h"

void INITIALIZE(FRAMEWORK* GAME)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
         SDL_GetError();
        exit(1);
    }

    
    GAME->MENU_STATE = true;
    GAME->GAMEOVER = false;
    GAME->BACK_MENU = false;
    GAME->QUIT_GAME = false;
    GAME->Win = false;
    initializeAudio();

    
    srand(time(NULL));

    
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
         IMG_GetError();
        exit(1);
    }

    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
         Mix_GetError();
        exit(1);
    }

    
    if (TTF_Init() == -1) {
        TTF_GetError();
        exit(1);
    }

    // Load font
    GAME->font = TTF_OpenFont("resources/font.ttf", 24);
    if (GAME->font == NULL) {
         TTF_GetError();
        exit(1);
    }

    // Create game window
    GAME->window = SDL_CreateWindow("RUN AWAY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (GAME->window == NULL) {
        SDL_GetError();
        exit(1);
    }

    // Create renderer
    GAME->renderer = SDL_CreateRenderer(GAME->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (GAME->renderer == NULL) {
         SDL_GetError();
        exit(1);
    }
    TTF_SetFontStyle(GAME->font, TTF_STYLE_BOLD);
    // Set color
    GAME->white.r = 255;
    GAME->white.g = 255;
    GAME->white.b = 255;
    GAME->white.a = 0;
}

void MANAGE_FRAME(int time_begin)
{
    int endOfLoopTime = SDL_GetTicks() - time_begin;
    if (endOfLoopTime < (1000 / FPS)) {
        SDL_Delay((1000 / FPS) - endOfLoopTime);
    }
}

void manageTimer(FRAMEWORK* game, Timer* time_Data)
{
    CALCULATE_TIME(time_Data);
    DISPLAY_TIME(game, time_Data);
}

static void CALCULATE_TIME(Timer* time_Data)
{
    time_t currentTime = time(NULL);
    int timeElapsed = (int)difftime(currentTime, time_Data->TIME_START);

    if (timeElapsed >= (TIMER_MINUTES * 60)) 
    {
        time_Data->TIME_REMAIN = 0;
    }
    else {
        time_Data->TIME_REMAIN = (TIMER_MINUTES * 60) - timeElapsed;
    }

    time_Data->MINUTE_REMAIN = time_Data->TIME_REMAIN / 60;
    time_Data->SECOND_REMAIN = time_Data->TIME_REMAIN % 60;
}
static void DISPLAY_TIME(FRAMEWORK* game, Timer* time_Data)
{
    static Image toDisplay = { 0, NULL, {0, 0, 91, 35} };
    toDisplay.rectangle.x = (SCREEN_WIDTH - toDisplay.rectangle.w) / 2;
    toDisplay.rectangle.y = 15;
    static int lastSeenTimeRemainingValue = 0;
    char numbersToPrint[8];

    if (lastSeenTimeRemainingValue != time_Data->TIME_REMAIN) {
        lastSeenTimeRemainingValue = time_Data->TIME_REMAIN;

        snprintf(numbersToPrint, sizeof(numbersToPrint), "%02d:%02d", time_Data->MINUTE_REMAIN, time_Data->SECOND_REMAIN);

        SDL_Surface* surface = TTF_RenderText_Solid(game->font, numbersToPrint, game->white);
        if (surface == NULL) {
             TTF_GetError();
        }

        if (toDisplay.texture != NULL) {
            SDL_DestroyTexture(toDisplay.texture);
        }

        toDisplay.texture = SDL_CreateTextureFromSurface(game->renderer, surface);
        if (toDisplay.texture == NULL) {
             SDL_GetError();
        }

        SDL_FreeSurface(surface);
    }

    DRAW_RECT(game->renderer, 590, 10, 100, 50);
    SDL_RenderCopy(game->renderer, toDisplay.texture, NULL, &toDisplay.rectangle);

    if (time_Data->TIME_REMAIN == 0) 
    {
        SDL_DestroyTexture(toDisplay.texture);
    }
}
static void DRAW_RECT(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    SDL_Rect rectangle = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}
void DISPLAY_GAMEOVER(FRAMEWORK* game, Timer* time_Data)
{
    SDL_Texture* background = NULL;
    if (game->GAMEOVER)
    { 
        background = IMG_LoadTexture(game->renderer, "resources/Game_over.png");
        if (!background) {
            IMG_GetError();
            return;
        }
        SDL_Surface* menuOptionSurface = TTF_RenderText_Solid(game->font, "Go Back to Menu", game->white);
        SDL_Texture* menuOptionTexture = SDL_CreateTextureFromSurface(game->renderer, menuOptionSurface);
        SDL_Rect menuOptionRect = { (SCREEN_WIDTH - menuOptionSurface->w) / 2, ((SCREEN_HEIGHT + 140) + menuOptionSurface->h) / 2, menuOptionSurface->w, menuOptionSurface->h };
        SDL_Surface* quitOptionSurface = TTF_RenderText_Solid(game->font, "Quit", game->white);
        SDL_Texture* quitOptionTexture = SDL_CreateTextureFromSurface(game->renderer, quitOptionSurface);
        SDL_Rect quitOptionRect = { (SCREEN_WIDTH - quitOptionSurface->w) / 2, ((SCREEN_HEIGHT + 280) + quitOptionSurface->h) / 2, quitOptionSurface->w, quitOptionSurface->h };

        while (game->BACK_MENU == false && game->QUIT_GAME == false) 
        {
            while (SDL_PollEvent(&game->event)) 
            {
                if (game->event.type == SDL_MOUSEBUTTONDOWN) 
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= menuOptionRect.x && mouseX < menuOptionRect.x + menuOptionRect.w && mouseY >= menuOptionRect.y && mouseY < menuOptionRect.y + menuOptionRect.h) {
                        game->BACK_MENU = true;
                    }
                    else if (mouseX >= quitOptionRect.x && mouseX < quitOptionRect.x + quitOptionRect.w && mouseY >= quitOptionRect.y && mouseY < quitOptionRect.y + quitOptionRect.h) {
                        game->QUIT_GAME = true;
                    }
                }
            }
            SDL_RenderCopy(game->renderer, background, NULL, NULL);
            SDL_RenderCopy(game->renderer, menuOptionTexture, NULL, &menuOptionRect);
            SDL_RenderCopy(game->renderer, quitOptionTexture, NULL, &quitOptionRect);
            SDL_RenderPresent(game->renderer);
         }
        if (game->BACK_MENU)
        {
            game->MENU_STATE = true;
            game->GAMEOVER = false;
            game->BACK_MENU = false;
            game->QUIT_GAME = false;
            game->Win = false;
            changeThemeSong();
        }
        else if (game->QUIT_GAME)
        {
            game->QUIT = true;
        }
        SDL_FreeSurface(menuOptionSurface);
        SDL_FreeSurface(quitOptionSurface);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(menuOptionTexture);
        SDL_DestroyTexture(quitOptionTexture);
    }
    if (game->Win)
    {
        background = IMG_LoadTexture(game->renderer, "resources/game_win.png");
        if (!background) {
            IMG_GetError();
            return;
        }
        SDL_Surface* menuOptionSurface = TTF_RenderText_Solid(game->font, "Go Back to Menu", game->white);
        SDL_Texture* menuOptionTexture = SDL_CreateTextureFromSurface(game->renderer, menuOptionSurface);
        SDL_Rect menuOptionRect = { (SCREEN_WIDTH - menuOptionSurface->w) / 2 , ((SCREEN_HEIGHT + 140) + menuOptionSurface->h) / 2 + 70 , menuOptionSurface->w, menuOptionSurface->h };
        SDL_Surface* quitOptionSurface = TTF_RenderText_Solid(game->font, "Quit", game->white);
        SDL_Texture* quitOptionTexture = SDL_CreateTextureFromSurface(game->renderer, quitOptionSurface);
        SDL_Rect quitOptionRect = { (SCREEN_WIDTH - quitOptionSurface->w) / 2, ((SCREEN_HEIGHT + 280) + quitOptionSurface->h) / 2 + 80, quitOptionSurface->w, quitOptionSurface->h };

        while (game->BACK_MENU == false && game->QUIT_GAME == false)
        {
            while (SDL_PollEvent(&game->event))
            {
                if (game->event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= menuOptionRect.x && mouseX < menuOptionRect.x + menuOptionRect.w && mouseY >= menuOptionRect.y && mouseY < menuOptionRect.y + menuOptionRect.h) {
                        game->BACK_MENU = true;
                    }
                    else if (mouseX >= quitOptionRect.x && mouseX < quitOptionRect.x + quitOptionRect.w && mouseY >= quitOptionRect.y && mouseY < quitOptionRect.y + quitOptionRect.h) {
                        game->QUIT_GAME = true;
                    }
                }
            }
            SDL_RenderCopy(game->renderer, background, NULL, NULL);
            SDL_RenderCopy(game->renderer, menuOptionTexture, NULL, &menuOptionRect);
            SDL_RenderCopy(game->renderer, quitOptionTexture, NULL, &quitOptionRect);
            SDL_RenderPresent(game->renderer);
        }
        if (game->BACK_MENU)
        {
            game->MENU_STATE = true;
            game->GAMEOVER = false;
            game->BACK_MENU = false;
            game->QUIT_GAME = false;
            game->Win = false;
            changeThemeSong();
        }
        else if (game->QUIT_GAME)
        {
            game->QUIT = true;
        }
        SDL_FreeSurface(menuOptionSurface);
        SDL_FreeSurface(quitOptionSurface);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(menuOptionTexture);
        SDL_DestroyTexture(quitOptionTexture);
    }
    
}

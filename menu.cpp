#include "menu.h"

int manageMenu(FRAMEWORK* game, Player players)
{
    int scene = 0;
    int player=-1;
    while (game->MENU_STATE) 
    {
         if (scene == 0) {
            handleMenuEntry(&scene, game);
        }
        else if (scene == 1) {
            player= handleHostGameOption(&scene, game);
        }
        else if (scene == 2) 
        {
            Rule_Option(&scene,game);
        }
        else if (scene == 3) {
            handleSettingsOption(&scene, game);
        }
    }
    return player;
}

 int displayOptions(FRAMEWORK* game, Menu* menu) {
    SDL_Rect textBoxRectangle[MAX_NUMBER_OF_TEXT_BOXES + 1];
    SDL_Texture* textBoxTexture[MAX_NUMBER_OF_TEXT_BOXES + 1];
    SDL_Texture* backgroundTexture = IMG_LoadTexture(game->renderer, menu->imageFilePath);
    SDL_Point mousePosition;

    prepareTextBoxesToBeShown(game, menu, textBoxRectangle, textBoxTexture);

    int selectedOption = -1;
    while (selectedOption == -1) 
    {
        while (SDL_PollEvent(&game->event))
        {
            switch (game->event.type) {
            case SDL_QUIT:
                game->MENU_STATE= false;
                game->QUIT= true;
                selectedOption = -2;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
                for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
                {
                    if (SDL_PointInRect(&mousePosition, &textBoxRectangle[i])) {
                        selectedOption = i;
                    }
                }
                break;
            default:
                break;
            }
        }

        SDL_RenderCopy(game->renderer, backgroundTexture, NULL, NULL);
        for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
        {
            if(menu->options[i]!="a") SDL_RenderCopy(game->renderer, textBoxTexture[i], NULL, &textBoxRectangle[i]);
        }
        SDL_RenderPresent(game->renderer);
    }

    SDL_DestroyTexture(backgroundTexture);
    destroyBoxTextures(menu, textBoxTexture);

    return selectedOption;
}

 void prepareTextBoxesToBeShown(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]) {
    SDL_Surface* textBoxSurface[MAX_NUMBER_OF_TEXT_BOXES + 1];
    int largestTextBoxWidth = 0;
    int accumulatedTextBoxHeight = 0;

    for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
    {
        
            textBoxSurface[i] = TTF_RenderText_Solid(game->font, menu->options[i], game->white);
            textBoxRectangle[i].y = accumulatedTextBoxHeight;
            textBoxRectangle[i].w = textBoxSurface[i]->w;
            textBoxRectangle[i].h = textBoxSurface[i]->h;
            accumulatedTextBoxHeight += textBoxRectangle[i].h + SPACING_BETWEEN_TEXT_BOXES;
            if (textBoxRectangle[i].w > largestTextBoxWidth) {
                largestTextBoxWidth = textBoxRectangle[i].w;
            }
    }

    int menuX = (SCREEN_WIDTH / 2) - (largestTextBoxWidth / 2);
    int menuY = (SCREEN_HEIGHT / 2) - LOCATION_ADJUSTMENT;
    for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
    {
       
            textBoxRectangle[i].x = menuX + (largestTextBoxWidth - textBoxRectangle[i].w) / 2;
            textBoxRectangle[i].y = menuY + textBoxRectangle[i].y;
        
        
    }

    for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
    {
        if (menu->options[i] != "a")
        {
            textBoxTexture[i] = SDL_CreateTextureFromSurface(game->renderer, textBoxSurface[i]);
            SDL_FreeSurface(textBoxSurface[i]);
        }
    }
}

 void destroyBoxTextures(Menu* menu, SDL_Texture* textBoxTexture[]) 
 {
    for (int i = 0; strcmp(menu->options[i], "\0") != 0; i++) 
    {
        if(menu->options[i]!="a") SDL_DestroyTexture(textBoxTexture[i]);
    }
}

 void updateBoxContent(FRAMEWORK* game, Menu* menu, SDL_Rect textBoxRectangle[], SDL_Texture* textBoxTexture[]) {
    int boxesChanged = 0;
    for (int i = 0; i < 5; i++) 
    {
            boxesChanged++;
    }
    if (boxesChanged > 0) {
        destroyBoxTextures(menu, textBoxTexture);
        prepareTextBoxesToBeShown(game, menu, textBoxRectangle, textBoxTexture);
    }
}

 void handleMenuEntry(int* scene, FRAMEWORK* game) {
    Menu menu = { {"Play Game", "Rule", "Settings", "Quit", "\0"}, {"resources/start_menu.png"} };
    int selectedBox = displayOptions(game, &menu);
    switch (selectedBox) 
    {
    case 0:
        playMenuClickSound();
        *scene = 1;
        break;
    case 1:
        playMenuClickSound();
        *scene = 2;
        break;
    case 2:
        playMenuClickSound();
        *scene = 3;
        break;
    case 3:
        game->MENU_STATE = false;
        game->QUIT = true;
        break;
    default:
        break;
    }
}

 int handleHostGameOption(int* scene, FRAMEWORK* game) {
    Menu menu = { {"choose", "choose", "choose", "choose", "choose", "Play", "Back", "\0"}, {"resources/lobby_menu.png"} };
    int selectedBox = 0;
    while (game->MENU_STATE)
    {
        selectedBox = displayOptions(game, &menu);
        if (selectedBox == 0) PLAYER_NUMBER = 0;
        else if (selectedBox == 1)  PLAYER_NUMBER = 1;

        else if (selectedBox == 2)  PLAYER_NUMBER = 2;
        else if (selectedBox == 3)  PLAYER_NUMBER = 3;
        else if (selectedBox == 4)  PLAYER_NUMBER = 4;

        if (selectedBox == 5 || selectedBox == 6)
        {   
            break;
        }
    }
    if (!game->MENU_STATE) 
    {
        *scene = 0;
    }
    else if (selectedBox == 5) 
    {
        playMenuClickSound();
        changeThemeSong();
        game->MENU_STATE= false;
        return PLAYER_NUMBER;
    }
    else 
    {
        playMenuClickSound();
        *scene = 0;
    }
    
}

 void Rule_Option(int* scene, FRAMEWORK* game)
{
     Menu menu = { {" ", " ", " ", " ", " ", " ", "Back", "\0"}, {"resources/Luat_choi.png"} };
     int selectedBox = displayOptions(game,&menu);
     switch (selectedBox)
     {
     case 6:
         playMenuClickSound();
         if (game->MENU_STATE && game->PAUSE)
         {
             game->MENU_STATE = false;
             game->PAUSE = false;
         }
         else
         {
             *scene = 0;
         }
         break;
     default:
         break;
     }
     

}

void handleSettingsOption(int* scene, FRAMEWORK* game) {
    Menu menu = { {"Mute Song", " ", " ", "Back to Menu", "\0"}, {"resources/settings_menu.png"} };
    int selectedBox = displayOptions(game, &menu);
    switch (selectedBox) {
    case 0:
        playMenuClickSound();
        if (!game->MUTE) {
            Mix_VolumeMusic(0);
            game->MUTE = true;
        }
        else {
            Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
            game->MUTE = false;
        }
        break;
    case 3:
        playMenuClickSound();
        if (game->MENU_STATE && game->PAUSE) {
            game->MENU_STATE = false;
            game->PAUSE = false;
        }
        else {
            *scene = 0;
        }
        break;
    default:
        break;
    }
}

 
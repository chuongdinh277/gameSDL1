#include "map.h"




int getNumberOfRowsInMap() 
{
    return MAP_ROWS;
}

int getNumberOfColumnsInMap() 
{
    return MAP_COLUMNS;
}

int getTheWidthOfTheTile() {
    return TILE_WIDTH;
}

int getTheHeightOfTheTile() {
    return TILE_HEIGHT;
}

int getTileInformation(int x, int y) {

    return mapGrid[x][y];
}

int encountersForbiddenTile(int x, int y) 
{
    int tileX = y / 32;
    int tileY = x / 32;
    return 0;
}

void renderBackground(FRAMEWORK* game, Background resources, Camera* camera) {
    SDL_Rect position;
    position.w = getTheWidthOfTheTile();
    position.h = getTheHeightOfTheTile();
    for (int i = 0; i < getNumberOfColumnsInMap(); i++) {
        for (int j = 0; j < getNumberOfRowsInMap(); j++) {
            position.x = j * 32 - camera->x;
            position.y = i * 32 - camera->y;
            SDL_RenderCopyEx(game->renderer, resources.tileAtlas, &resources.tilesGraphic[getTileInformation(i, j)], &position, 0, NULL, SDL_FLIP_NONE);
        }
    }
}
void initiateMapResources(SDL_Renderer* renderer, Background* resources) {
    resources->tileAtlas = IMG_LoadTexture(renderer, "resources/Tiles3.png");
    int tileIndex = 0;
    for (int y = 0; y < 11; y++)
    {
        for (int x = 0; x < 9; x++) 
        {
            resources->tilesGraphic[tileIndex].x = x * 32;
            resources->tilesGraphic[tileIndex].y = y * 32;
            resources->tilesGraphic[tileIndex].w = 32;
            resources->tilesGraphic[tileIndex].h = 32;
            tileIndex++;
        }
    }
}


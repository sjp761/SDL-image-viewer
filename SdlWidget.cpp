#include "SdlWidget.h"

void SdlWidget::updateRenderer(SDL_Surface* surface)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    updateRenderer(texture);
}

void SdlWidget::updateRenderer(SDL_Texture *texture)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
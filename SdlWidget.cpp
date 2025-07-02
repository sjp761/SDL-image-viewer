#include "SdlWidget.h"
#include <iostream>
#include <QWindow>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

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

SdlWidget::SdlWidget(QWidget *parent)
    :QWidget(parent),
     renderer(nullptr),
     window(nullptr),
     texture(nullptr)
{
    if (!window) {
        window = SDL_CreateWindowFrom(reinterpret_cast<void*>(winId()));
        if (!window) {
            std::cerr << "SDL_CreateWindowFrom failed: " << SDL_GetError() << std::endl;
            return;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
            return;
        }
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

SDL_Surface* SdlWidget::loadImage(const std::string& imagePath)
{
    SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
    if (!surface) {
        std::cerr << "SDL_LoadBMP failed: " << SDL_GetError() << std::endl;
    }
    return surface;
}

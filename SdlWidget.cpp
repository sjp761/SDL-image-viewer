#include "SdlWidget.h"
#include <iostream>
#include <QWindow>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>



void SdlWidget::updateRenderer(SDL_Surface* surface)
{
    if (!renderer || !surface) return;
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        std::cout << "Texture destroyed." << std::endl;
    }
    if (surface != nullptr) 
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

}

SdlWidget::SdlWidget(QWidget *parent)
    :QWidget(parent),
     renderer(nullptr),
     window(nullptr),
     texture(nullptr)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
}

SdlWidget::~SdlWidget()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
}

void SdlWidget::showEvent(QShowEvent* event) //Initializes stuff before widget is shown, will not work if called during the constructor
{
    QWidget::showEvent(event);
    if (!window) {
        window = SDL_CreateWindowFrom(reinterpret_cast<void*>(winId()));
        if (!window) {
            std::cerr << "SDL_CreateWindowFrom failed: " << SDL_GetError() << std::endl;
            return;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
            return;
        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer); // Present the initial draw
    }
}

void SdlWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    std::cout << "Paint event triggered." << std::endl;
    if (!startup && renderer && surface) // Check if startup is false and both renderer and surface are valid
    {
        updateRenderer(surface); // Ensure the renderer is updated with the current surface
    }
}


SDL_Surface* SdlWidget::loadImage(const std::string& imagePath)
{
    SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
    if (!surface) {
        std::cerr << "SDL_LoadBMP failed: " << SDL_GetError() << std::endl;
    }
    return surface;
}

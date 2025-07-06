#include "SDLContainer.h"
#include <iostream>
#include <QWindow>
#include <QTimer>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>

using SDLTexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDLTextureDeleter)>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDLSurfaceDeleter)>;

SDL_Renderer* SDLContainer::renderer = nullptr;
SDL_Window* SDLContainer::window = nullptr;
SDLTexturePtr SDLContainer::texture(nullptr, SDLTextureDeleter);
SDLSurfacePtr SDLContainer::surface(nullptr, SDLSurfaceDeleter);
QWindow* SDLContainer::embedded = nullptr;

void SDLContainer::initSDL()
{
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
    
    window = SDL_CreateWindow("SDL Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Unable to create SDL window: %s\n", SDL_GetError());
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Unable to create SDL renderer: %s\n", SDL_GetError());
        return;
    }
    surface.reset(SDL_CreateRGBSurface(0, 640, 480, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
    SDL_FillRect(surface.get(), NULL, SDL_MapRGB(surface->format, rand() % 256, rand() % 256, rand() % 256)); //Random color background
    texture.reset(SDL_CreateTextureFromSurface(renderer, surface.get()));
    
    render();
}

void SDLContainer::createNativeWindow()
{
    if (!window) {
        printf("Error: SDL window is null\n");
        return;
    }

    
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    if (!SDL_GetWindowWMInfo(window, &info)) {
        printf("Failed to get window info: %s\n", SDL_GetError());
        return;
    }
    
    if (info.subsystem != SDL_SYSWM_X11) {
        printf("Error: Not running on X11\n");
        return;
    }
    
    embedded = QWindow::fromWinId(static_cast<WId>(info.info.x11.window));
    if (!embedded) {
        printf("Error: Failed to create QWindow from native handle\n");
        return;
    }
    
    // Don't hide the window - the QWindow needs the SDL window to remain visible
    printf("Successfully created embedded QWindow\n");
}

void SDLContainer::loadImage(const std::string &fileName)
{
 
    
    // Load new image
    surface.reset(IMG_Load(fileName.c_str())); 
    // Create texture from surface
    texture.reset(SDL_CreateTextureFromSurface(renderer, surface.get()));
    if (!texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
        return;
    }
}

void SDLContainer::render()
{
    if (!renderer) {
        return;
    }
    std::cout << "Rendering SDL content" << std::endl;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture.get(), NULL, NULL);    
    SDL_RenderPresent(renderer);
}

void SDLContainer::resize(int width, int height)
{
    if (!window) {
        printf("Error: SDL window is null\n");
        return;
    }
    
    SDL_SetWindowSize(window, width, height);
}
    


#include "SDLContainer.h"
#include <iostream>
#include <QWindow>
#include <QTimer>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>
#include "SDL_SmartPointer.h"

SDL_SmartPointer<SDL_Texture> SDLContainer::texture(nullptr);
SDL_SmartPointer<SDL_Surface> SDLContainer::surface(nullptr);
SDL_Renderer* SDLContainer::renderer = nullptr;
SDL_Window* SDLContainer::window = nullptr;
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
    surface.ptr.reset(SDL_CreateRGBSurface(0, 640, 480, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
    SDL_FillRect(surface.ptr.get(), NULL, SDL_MapRGB(surface.ptr->format, rand() % 256, rand() % 256, rand() % 256)); //Random color background
    texture.ptr.reset(SDL_CreateTextureFromSurface(renderer, surface.ptr.get()));

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
    surface.ptr.reset(IMG_Load(fileName.c_str()));
    // Create texture from surface
    texture.ptr.reset(SDL_CreateTextureFromSurface(renderer, surface.ptr.get()));
    if (!texture.ptr.get()) {
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
    SDL_RenderCopy(renderer, texture.ptr.get(), NULL, NULL);
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
    


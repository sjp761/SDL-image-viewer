#include "SDLContainer.h"
#include <iostream>
#include <QWindow>
#include <QTimer>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>
#include "SDL_SmartPointer.h"

namespace {
    constexpr int DEFAULT_WINDOW_WIDTH = 800;
    constexpr int DEFAULT_WINDOW_HEIGHT = 600;
    constexpr int DEFAULT_SURFACE_WIDTH = 640;
    constexpr int DEFAULT_SURFACE_HEIGHT = 480;
    constexpr int SURFACE_DEPTH = 32;
    constexpr Uint32 RED_MASK = 0x00FF0000;
    constexpr Uint32 GREEN_MASK = 0x0000FF00;
    constexpr Uint32 BLUE_MASK = 0x000000FF;
    constexpr Uint32 ALPHA_MASK = 0xFF000000;
    constexpr int COLOR_MAX_VALUE = 256;
    constexpr int RENDERER_INDEX = -1;
}

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
                              DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Unable to create SDL window: %s\n", SDL_GetError());
        return;
    }
    
    renderer = SDL_CreateRenderer(window, RENDERER_INDEX, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Unable to create SDL renderer: %s\n", SDL_GetError());
        return;
    }
    surface.reset(SDL_CreateRGBSurface(0, DEFAULT_SURFACE_WIDTH, DEFAULT_SURFACE_HEIGHT, SURFACE_DEPTH, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK));
    SDL_FillRect(surface.get(), NULL, SDL_MapRGB(surface->format, rand() % COLOR_MAX_VALUE, rand() % COLOR_MAX_VALUE, rand() % COLOR_MAX_VALUE)); //Random color background
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
    if (!texture.get()) {
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



#include "Renderer.h"

SDL_Texture *Renderer::loadTexture(std::string path)
{
    if (sdl_texture != nullptr) {
        SDL_DestroyTexture(sdl_texture); // Free the previous texture if it exists, prevents from piling up textures in memory
    }
    sdl_texture = IMG_LoadTexture(sdl_renderer, path.c_str());
    if (sdl_texture == nullptr) {
        printf("Failed to load texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    return sdl_texture;
}

void Renderer::updateRenderer(SDL_Surface* surface)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    updateRenderer(texture);
}

void Renderer::updateRenderer(SDL_Texture *texture)
{
    SDL_RenderClear(sdl_renderer);
    SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
    SDL_RenderPresent(sdl_renderer);
}

Renderer::Renderer(SDL_Window *window)
    : sdl_texture(nullptr)
{
    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdl_renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }
    //SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Renderer::Renderer()
    : sdl_renderer(nullptr), sdl_texture(nullptr)
{
    //Blank
}
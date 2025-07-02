#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <map>
#include "Surface.h"

class Renderer
{
public:
    SDL_Renderer* sdl_renderer;
    SDL_Texture* sdl_texture;

    SDL_Texture* loadTexture(std::string path);
    void updateRenderer(SDL_Surface* surface);
    void updateRenderer(SDL_Texture* texture);
    Renderer(SDL_Window* window); // Parameterized constructor
    Renderer(); // Default constructor declaration
};
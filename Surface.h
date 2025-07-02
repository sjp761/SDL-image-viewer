#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#pragma once

class Surface
{
    public:
    Surface() : sdl_surface(nullptr), 
                sdl_sub_surface(nullptr) 
    {
        //blank
    }
    SDL_Surface* sdl_surface;
    SDL_Surface* sdl_sub_surface;
    enum KeyboardKeypresses
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
    };
    std::map<KeyboardKeypresses, SDL_Surface*> keyPressSurfacesBMP;
    void freeColorSurface(SDL_Surface* surface);
    SDL_Surface* randomColorSurface();
    SDL_Surface *loadImage(const std::string& imagePath);


    void loadKeyPressImagesBMP();
    ~Surface();
};
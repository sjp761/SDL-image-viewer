#include "Surface.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

void Surface::loadKeyPressImagesBMP() 
{
    keyPressSurfacesBMP[KEY_PRESS_SURFACE_DEFAULT] = loadImage("images/press.bmp");
    keyPressSurfacesBMP[KEY_PRESS_SURFACE_UP] = loadImage("images/up.bmp");
    keyPressSurfacesBMP[KEY_PRESS_SURFACE_DOWN] = loadImage("images/down.bmp");
    keyPressSurfacesBMP[KEY_PRESS_SURFACE_LEFT] = loadImage("images/left.bmp");
    keyPressSurfacesBMP[KEY_PRESS_SURFACE_RIGHT] = loadImage("images/right.bmp");
}
Surface::~Surface()
{
    for (auto& pair : keyPressSurfacesBMP) 
    {
        if (pair.second) SDL_FreeSurface(pair.second);
    }
    if (sdl_surface) SDL_FreeSurface(sdl_surface);
    if (sdl_sub_surface) SDL_FreeSurface(sdl_sub_surface);
}
void Surface::freeColorSurface(SDL_Surface *surface)
{
    if (surface != nullptr && surface != keyPressSurfacesBMP[KEY_PRESS_SURFACE_DEFAULT] &&
        surface != keyPressSurfacesBMP[KEY_PRESS_SURFACE_UP] &&
        surface != keyPressSurfacesBMP[KEY_PRESS_SURFACE_DOWN] &&
        surface != keyPressSurfacesBMP[KEY_PRESS_SURFACE_LEFT] &&
        surface != keyPressSurfacesBMP[KEY_PRESS_SURFACE_RIGHT])
    {
        SDL_FreeSurface(surface);
    }
}

SDL_Surface *Surface::randomColorSurface()
{
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, 640, 480, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(tempSurface, NULL, SDL_MapRGB(tempSurface->format, rand() % 256, rand() % 256, rand() % 256));
    return tempSurface; 
}

SDL_Surface* Surface::loadImage(const std::string& imagePath)
{
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath.c_str(), IMG_GetError());
        return nullptr;
    }
    //SDL_Surface* optimized = SDL_ConvertSurface(loadedSurface, sdl_surface->format, 0); <- old surface code
    //SDL_FreeSurface(loadedSurface); // Free the original surface <- old surface code
    //return optimized; // Return the optimized surface <- old surface code
    return loadedSurface; // Return the loaded surface
}
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <QWindow>
#include <iostream>
#include <memory>

inline void SDLTextureDeleter(SDL_Texture* texture);
inline void SDLSurfaceDeleter(SDL_Surface* surface);

using SDLTexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDLTextureDeleter)>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDLSurfaceDeleter)>;

class SDLContainer
{
   public: 
        static SDL_Renderer *renderer;
        static SDL_Window *window;
        static SDLTexturePtr texture;
        static SDLSurfacePtr surface;
        static QWindow* embedded;
        static void render();
        static void initSDL();
        static void createNativeWindow();
        static void loadImage(const std::string &fileName);
        static void resize(int width, int height);

};

// Custom deleter for SDL_Texture
inline void SDLTextureDeleter(SDL_Texture* texture) {
        if (texture) {
                std::cout << "Deleted surface" << std::endl;
                SDL_DestroyTexture(texture);
        }
}

// Custom deleter for SDL_Surface
inline void SDLSurfaceDeleter(SDL_Surface* surface) {
        if (surface) {
                std::cout << "Deleted texture" << std::endl;
                SDL_FreeSurface(surface);
        }
}
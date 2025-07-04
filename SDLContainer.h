#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <QWindow>

class SDLContainer
{
   public: 
        static SDL_Renderer *renderer;
        static SDL_Window *window;
        static SDL_Texture *texture;
        static SDL_Surface *surface;
        static QWindow* embedded;
        static void render();
        static void initSDL();
        static void createNativeWindow();
        static void loadImage(const std::string &fileName);

};
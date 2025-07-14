#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <QWindow>
#include <iostream>
#include <memory>
#include "SDL_SmartPointer.h"

class SDLContainer
{
   public: 
        static SDL_Renderer *renderer;
        static SDL_Window *window;
        static SDL_SmartPointer<SDL_Texture> texture;
        static SDL_SmartPointer<SDL_Surface> surface;
        static QWindow* embedded;
        static void render();
        static void initSDL();
        static void createNativeWindow();
        static void loadImage(const std::string &fileName);
        static void resize(int width, int height);

};
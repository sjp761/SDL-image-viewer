#pragma once

#include <QWidget>
#include <SDL2/SDL.h>

class SdlWidget : public QWidget
{
    Q_OBJECT

    public:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture *texture;
        void updateRenderer(SDL_Surface* surface);
        void updateRenderer(SDL_Texture* texture);

};
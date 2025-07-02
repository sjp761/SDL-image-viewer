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
        SDL_Surface *surface;
        void updateRenderer(SDL_Surface* surface);
        void updateRenderer(SDL_Texture* texture);
        SdlWidget(QWidget *parent = nullptr);
        ~SdlWidget();
        SDL_Surface* loadImage(const std::string& imagePath);
        void showEvent(QShowEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
};
#include "Surface.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <QWidget>
#include <map>
#include <string>
#pragma once

class Window
{
    public:

        QWidget
        Surface surface;
        Renderer renderer;
};
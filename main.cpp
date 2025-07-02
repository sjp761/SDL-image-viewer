#include "mainwindow.h"

#include <QApplication>
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    setenv("QT_QPA_PLATFORM", "xcb", 1);
    setenv("SDL_VIDEODRIVER", "x11", 1);
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

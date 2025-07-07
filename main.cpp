#include "mainwindow.h"
#include "SDLWidget.h"
#include <QApplication>
#include <SDL2/SDL.h>
#include <iostream>
#include "SDLContainer.h"
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{
    setenv("QT_QPA_PLATFORM", "xcb", 1);
    setenv("SDL_VIDEODRIVER", "x11", 1);
    QApplication a(argc, argv);
    SDLContainer::initSDL(); //Initialize after starting application but before creating the main window - helps with adding widget after creating main window
    SDL_PumpEvents();
    SDLContainer::createNativeWindow();
    MainWindow w;
    w.fillRecentSet(); // Fill the recent files set from the file
    w.updateRecentFileMenu();
    w.show();
    return a.exec();
}

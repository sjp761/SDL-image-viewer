#include "Window.h"
#include "Surface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <cstdlib>

Window::Window()
{
    sdl_window = nullptr; // Initialize SDL components
}


void Window::startApp()
{
    sdl_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = Renderer(sdl_window); // Initialize the renderer with the created window
    //surface.sdl_surface = SDL_GetWindowSurface(sdl_window);
    //SDL_FillRect(surface.sdl_surface, NULL, SDL_MapRGB(surface.sdl_surface->format, 0xFF, 0xFF, 0xFF)); <- old surface code
    //SDL_UpdateWindowSurface(sdl_window); <- old surface code
    surface.loadKeyPressImagesBMP();
    surface.sdl_sub_surface = surface.keyPressSurfacesBMP.at(Surface::KEY_PRESS_SURFACE_DEFAULT);
    renderer.updateRenderer(surface.sdl_sub_surface); // Update the renderer with the default surface
    bool quitFlag = false;
    while (!quitFlag)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quitFlag = true;
            }
            const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_UP])
            {
                updateSubsurface(surface.keyPressSurfacesBMP.at(Surface::KEY_PRESS_SURFACE_UP)); // Update the subsurface to the up key surface
            }
            if (currentKeyStates[SDL_SCANCODE_DOWN])
            {
                updateSubsurface(surface.keyPressSurfacesBMP.at(Surface::KEY_PRESS_SURFACE_DOWN));
            }
            if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                updateSubsurface(surface.keyPressSurfacesBMP.at(Surface::KEY_PRESS_SURFACE_LEFT));
            }
            if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                updateSubsurface(surface.keyPressSurfacesBMP.at(Surface::KEY_PRESS_SURFACE_RIGHT));
            }
            if (currentKeyStates[SDL_SCANCODE_SPACE])
            {
                updateSubsurface(surface.randomColorSurface()); // Update the subsurface to a random color surface
            }
            if (currentKeyStates[SDL_SCANCODE_R])
            {
                surface.freeColorSurface(surface.sdl_sub_surface); // Free the previous surface
                surface.sdl_sub_surface = nullptr; // Set to null since we're using a texture now
                renderer.sdl_texture = renderer.loadTexture("images/texture.png");
                renderer.updateRenderer(renderer.sdl_texture); // Update the renderer with the new texture
            }
        }
    }
}

void Window::updateSubsurface(SDL_Surface *subsurface)
{
    surface.freeColorSurface(surface.sdl_sub_surface);
    surface.sdl_sub_surface = subsurface;
    renderer.updateRenderer(surface.sdl_sub_surface);
}

Window::~Window()
{
    if (sdl_window) SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

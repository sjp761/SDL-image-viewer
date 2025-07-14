#pragma once
#include <memory>

template <typename T>
struct SDL_Deleter {
    void operator()(SDL_Texture* ptr) const {
        SDL_DestroyTexture(ptr);
        std::cout << "SDL_Texture deleted" << std::endl;
    }

    void operator()(SDL_Surface* ptr) const {
        SDL_FreeSurface(ptr);
        std::cout << "SDL_Surface deleted" << std::endl;
    }
};

template <typename T>
class SDL_SmartPointer 
{
    public:
        std::unique_ptr<T, SDL_Deleter<T>> ptr;
        SDL_SmartPointer(T* ptr) : ptr(ptr, SDL_Deleter<T>()) {}

};
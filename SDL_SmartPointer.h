#pragma once
#include <memory>
#include <SDL.h>
#include <iostream>

// Primary template: does nothing by default
template <typename T>
struct SDL_Deleter {
    void operator()(T* ptr) const {
        // static_assert to catch unsupported types at compile time
        static_assert(sizeof(T) == 0, "SDL_Deleter not specialized for this type");
    }
};

// Specialization for SDL_Texture
template <>
struct SDL_Deleter<SDL_Texture> {
    void operator()(SDL_Texture* ptr) const {
        if (ptr) {
            SDL_DestroyTexture(ptr);
            std::cout << "SDL_Texture deleted" << std::endl;
        }
    }
};

// Specialization for SDL_Surface
template <>
struct SDL_Deleter<SDL_Surface> {
    void operator()(SDL_Surface* ptr) const {
        if (ptr) {
            SDL_FreeSurface(ptr);
            std::cout << "SDL_Surface deleted" << std::endl;
        }
    }
};

template <typename T>
class SDL_SmartPointer {
public:
    // Constructor
    explicit SDL_SmartPointer(T* rawPtr = nullptr)
        : ptr_(rawPtr) {}

    // Disable copy
    SDL_SmartPointer(const SDL_SmartPointer&) = delete;
    SDL_SmartPointer& operator=(const SDL_SmartPointer&) = delete;

    // Enable move
    SDL_SmartPointer(SDL_SmartPointer&&) noexcept = default;
    SDL_SmartPointer& operator=(SDL_SmartPointer&&) noexcept = default;

    // Accessors
    T* get() const { return ptr_.get(); }
    T* operator->() const { return ptr_.get(); }
    T& operator*() const { return *ptr_; }
    explicit operator bool() const { return static_cast<bool>(ptr_); } //Allows checking if the internal pointer is valid

    // Release ownership
    T* release() { return ptr_.release(); }

    // Reset pointer
    void reset(T* rawPtr = nullptr) { ptr_.reset(rawPtr); }

private:
    std::unique_ptr<T, SDL_Deleter<T>> ptr_;
};
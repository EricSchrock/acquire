#pragma once

#include "SDL.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Render(uint8_t brightness);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::size_t screen_width{(std::size_t)(900 * 1.618)};
    const std::size_t screen_height{900};
};
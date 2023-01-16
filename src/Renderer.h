#pragma once

#include <string>

#include "SDL.h"
#include "Tile.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderBoard(Tile tiles[tiles_up][tiles_across]);
    void RenderFPS(int fps);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::size_t screen_width{(std::size_t)(900 * 1.618)};
    const std::size_t screen_height{900};
};

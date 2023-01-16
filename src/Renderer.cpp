#include "Renderer.h"

#include <string>

Renderer::Renderer() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Acquire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::RenderGame(uint8_t brightness) {
    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Rect rectangle;
    rectangle.w = 100;
    rectangle.h = 100;
    rectangle.x = (screen_width / 2) - (rectangle.w / 2);
    rectangle.y = (screen_height / 2) - (rectangle.h / 2);

    SDL_SetRenderDrawColor(renderer, brightness, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderPresent(renderer);
}

void Renderer::RenderFPS(int fps) {
    std::string title{"Acquire (FPS: " + std::to_string(fps) + ")"};
    SDL_SetWindowTitle(window, title.c_str());
}

#include <iostream>
#include <random>
#include <thread>

#include "SDL.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Acquire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900 * 1.618, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Random number generator
    std::random_device random;
    std::mt19937 engine(random());

    auto then = std::chrono::system_clock::now();

    std::uniform_int_distribution<> duration_dist(250, 500);
    double duration = duration_dist(engine);

    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Reduce CPU load

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE)) {
                running = false;
            }
        }

        auto now = std::chrono::system_clock::now();
        long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
        if (elapsed >= duration) {
            SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            std::uniform_int_distribution<> size_dist(5, 500);
            std::uniform_int_distribution<> x_dist(0, 900 * 1.618);
            std::uniform_int_distribution<> y_dist(0, 900);

            SDL_Rect rectangle;
            rectangle.w = size_dist(engine);
            rectangle.h = size_dist(engine);
            rectangle.x = x_dist(engine);
            rectangle.y = y_dist(engine);

            std::uniform_int_distribution<> color_dist(0x00, 0xFF);
            SDL_SetRenderDrawColor(renderer, color_dist(engine), color_dist(engine), color_dist(engine), color_dist(engine));
            SDL_RenderFillRect(renderer, &rectangle);

            SDL_RenderPresent(renderer);

            duration = duration_dist(engine);
            then = now;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

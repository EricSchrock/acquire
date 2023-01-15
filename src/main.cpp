#include <iostream>
#include <random>
#include <thread>

#include "SDL.h"

int main() {
    constexpr float width = 900 * 1.618;
    constexpr float height = 900;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Acquire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Random number generator
    std::random_device random;
    std::mt19937 engine(random());

    auto then = std::chrono::system_clock::now();
    double duration = 10;  // ms

    bool reversed = true;
    uint8_t brightness = UINT8_MAX;

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

            SDL_Rect rectangle;
            rectangle.w = 100;
            rectangle.h = 100;
            rectangle.x = (width / 2) - (rectangle.w / 2);
            rectangle.y = (height / 2) - (rectangle.h / 2);

            SDL_SetRenderDrawColor(renderer, brightness, 0x00, 0x00, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rectangle);

            SDL_RenderPresent(renderer);

            if (brightness == UINT8_MAX)
                reversed = true;

            if (brightness == (UINT8_MAX / 2))
                reversed = false;

            (reversed) ? brightness-- : brightness++;

            then = now;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

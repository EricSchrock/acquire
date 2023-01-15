#include <iostream>
#include <random>
#include <thread>

#include "Renderer.h"
#include "SDL.h"

int main() {
    Renderer renderer;

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
            renderer.Render(brightness);

            if (brightness == UINT8_MAX)
                reversed = true;

            if (brightness == (UINT8_MAX / 2))
                reversed = false;

            (reversed) ? brightness-- : brightness++;

            then = now;
        }
    }
}

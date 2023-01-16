#include <iostream>
#include <random>
#include <thread>

#include "Renderer.h"
#include "SDL.h"

int main() {
    Renderer renderer;

    const std::size_t target_fps = 60;
    Uint32 target_frame_duration_ms = 1000 / target_fps;
    Uint32 target_title_duration_ms = 1000;

    Uint32 title_start = SDL_GetTicks();

    int frame_count = 0;

    bool reversed = true;
    uint8_t brightness = UINT8_MAX;

    bool running = true;
    while (running) {
        Uint32 frame_start = SDL_GetTicks();

        // Input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE)) {
                running = false;
            }
        }

        // Update
        if (brightness == UINT8_MAX)
            reversed = true;

        if (brightness == (UINT8_MAX / 2))
            reversed = false;

        (reversed) ? brightness-- : brightness++;

        // Render
        renderer.RenderBox(brightness);

        frame_count++;

        Uint32 frame_end = SDL_GetTicks();
        Uint32 frame_duration_ms = frame_end - frame_start;
        Uint32 title_duration_ms = frame_end - title_start;

        if (title_duration_ms >= target_title_duration_ms) {
            renderer.RenderFPS(frame_count);
            frame_count = 0;
            title_start = frame_end;
        }

        if (frame_duration_ms < target_frame_duration_ms) {
            SDL_Delay(target_frame_duration_ms - frame_duration_ms);
        }
    }
}

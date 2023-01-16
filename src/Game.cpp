#include "Game.h"

void Game::Run(Controller& controller, Renderer& renderer) {
    Uint32 title_start = SDL_GetTicks();

    int frame_count = 0;

    bool reversed = true;
    uint8_t brightness = UINT8_MAX;

    bool running = true;
    while (running) {
        Uint32 frame_start = SDL_GetTicks();

        controller.HandleInput(running);

        // Update
        if (brightness == UINT8_MAX)
            reversed = true;

        if (brightness == (UINT8_MAX / 2))
            reversed = false;

        (reversed) ? brightness-- : brightness++;

        // Render
        renderer.RenderGame(brightness);

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

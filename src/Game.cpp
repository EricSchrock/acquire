#include "Game.h"

void Game::Run(Controller& controller, Renderer& renderer) {
    Uint32 title_start = SDL_GetTicks();

    int frame_count = 0;

    bool running = true;
    while (running) {
        // The main game loop
        Uint32 frame_start = SDL_GetTicks();

        controller.HandleInput(running);
        Update();
        renderer.RenderGame(brightness);

        Uint32 frame_end = SDL_GetTicks();

        // The FPS tracker
        frame_count++;

        Uint32 title_duration_ms = frame_end - title_start;
        if (title_duration_ms >= target_title_duration_ms) {
            renderer.RenderFPS(frame_count);
            frame_count = 0;
            title_start = frame_end;
        }

        // The frame throttle
        Uint32 frame_duration_ms = frame_end - frame_start;
        if (frame_duration_ms < target_frame_duration_ms) {
            SDL_Delay(target_frame_duration_ms - frame_duration_ms);
        }
    }
}

void Game::Update() {
    if (brightness == UINT8_MAX)
        reversed = true;

    if (brightness == (UINT8_MAX / 2))
        reversed = false;

    (reversed) ? brightness-- : brightness++;
}

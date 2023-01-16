#include "Controller.h"

#include "SDL.h"

void Controller::HandleInput(bool& running, bool& player_done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                    player_done = true;
                    break;
            }
        }
    }
}

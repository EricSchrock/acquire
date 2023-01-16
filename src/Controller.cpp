#include "Controller.h"

#include "SDL.h"

void Controller::HandleInput(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if ((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE)) {
            running = false;
        }
    }
}

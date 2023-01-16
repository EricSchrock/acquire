#pragma once

#include "Controller.h"
#include "Renderer.h"

class Game {
public:
    void Run(Controller& controller, Renderer& renderer);

private:
    const unsigned int target_fps{60};
    const unsigned int target_frame_duration_ms{1000 / target_fps};
    const unsigned int target_title_duration_ms{1000};
};

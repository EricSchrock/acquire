#pragma once

#include "Controller.h"
#include "Entity.h"
#include "Renderer.h"
#include "Tile.h"

class Game {
public:
    Game(int num_players);

    void Run();

private:
    int num_players;

    const unsigned int target_fps{60};
    const unsigned int target_frame_duration_ms{1000 / target_fps};
    const unsigned int target_title_duration_ms{1000};

    Controller controller;
    Renderer renderer;

    Tile tiles[tiles_up][tiles_across];

    Entity bank{Color(0xFF, 0xFD, 0xD0)};   // Cream
    Entity board{Color(0x00, 0x00, 0x00)};  // Black

    void Update();
};

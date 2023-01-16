#pragma once

#include <vector>

#include "Controller.h"
#include "Player.h"
#include "Renderer.h"
#include "Tile.h"

class Game {
public:
    Game(int num_players);

    void Run();

private:
    int num_players;

    static constexpr unsigned int target_fps{60};
    static constexpr unsigned int target_frame_duration_ms{1000 / target_fps};
    static constexpr unsigned int target_title_duration_ms{1000};

    static constexpr unsigned int max_tiles{6};

    Controller controller;
    Renderer renderer;

    Tile tiles[tiles_up][tiles_across];

    std::vector<Player> players;
    unsigned int current_player_id{1};
    bool player_done{false};

    void Update();
};

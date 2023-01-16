#include "Game.h"

#include <random>

Game::Game(int num_players)
    : num_players(num_players) {
    std::random_device random;
    std::mt19937 engine(random());

    std::uniform_int_distribution<> row_dist(0, tiles_up - 1);
    std::uniform_int_distribution<> col_dist(0, tiles_across - 1);

    for (int i = 0; i < num_players;) {
        int row = row_dist(engine);
        int col = col_dist(engine);

        if (tiles[row][col].State() == TileState::InBag) {
            tiles[row][col].Place();
            i++;
        }
    }

    for (int i = 0; i < num_players; i++) {
        players.emplace_back(Player("Player " + std::to_string(i + 1)));

        for (int j = 0; j < max_tiles;) {
            int row = row_dist(engine);
            int col = col_dist(engine);

            if (tiles[row][col].State() == TileState::InBag) {
                tiles[row][col].Pick(&(*players.end()));
                j++;
            }
        }
    }
}

void Game::Run() {
    Uint32 title_start = SDL_GetTicks();

    int frame_count = 0;

    bool running = true;
    while (running) {
        // The main game loop
        Uint32 frame_start = SDL_GetTicks();

        controller.HandleInput(running);
        Update();
        renderer.RenderBoard(tiles);

        Uint32 frame_end = SDL_GetTicks();

        // The FPS tracker
        frame_count++;

        Uint32 title_duration_ms = frame_end - title_start;
        if (title_duration_ms >= target_title_duration_ms) {
            renderer.RenderFPS(frame_count);
            frame_count = 0;
            title_start = frame_end;
        }

        // The FPS throttle
        Uint32 frame_duration_ms = frame_end - frame_start;
        if (frame_duration_ms < target_frame_duration_ms) {
            SDL_Delay(target_frame_duration_ms - frame_duration_ms);
        }
    }
}

void Game::Update() {
}

#include "Game.h"

Game::Game(unsigned int num_players)
    : num_players(num_players), engine(device()), row_dist(0, tiles_up - 1), col_dist(0, tiles_across - 1) {
    // Place starting tiles (count = number of players)
    for (int i = 0; i < num_players;) {
        int row = row_dist(engine);
        int col = col_dist(engine);

        if (tiles[row][col].State() == TileState::InBag) {
            tiles[row][col].Place();
            i++;
        }
    }

    // Initialize players and give them tiles
    for (int id = 1; id <= num_players; id++) {
        players.emplace_back(Player(id));

        for (int count = 0; count < max_tiles;) {
            int row = row_dist(engine);
            int col = col_dist(engine);

            if (tiles[row][col].State() == TileState::InBag) {
                tiles[row][col].Pick(id);
                count++;
            }
        }
    }

    // Set the first selected tile
    bool tile_selected = false;
    for (int row = 0; row < tiles_up; row++) {
        for (int col = 0; col < tiles_across; col++) {
            if (tiles[row][col].OwnerID() == current_player_id) {
                tiles[row][col].Select();
                tile_selected = true;
                break;
            }
        }

        if (tile_selected)
            break;
    }
}

void Game::Run() {
    Uint32 title_start = SDL_GetTicks();

    int frame_count = 0;

    bool running = true;
    while (running) {
        // The main game loop
        Uint32 frame_start = SDL_GetTicks();

        controller.HandleInput(running, player_done, switch_active_tile);
        Update();
        renderer.RenderBoard(tiles, current_player_id);

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
    if (player_done) {
        // Place currently selected tile
        bool tile_placed = false;
        for (int row = 0; row < tiles_up; row++) {
            for (int col = 0; col < tiles_across; col++) {
                if (tiles[row][col].State() == Selected) {
                    tiles[row][col].Place();
                    tile_placed = true;
                    break;
                }
            }

            if (tile_placed)
                break;
        }

        // Give the current player a new tile
        bool tile_available = false;
        for (int row = 0; row < tiles_up; row++) {
            for (int col = 0; col < tiles_across; col++) {
                if (tiles[row][col].State() == InBag) {
                    tile_available = true;
                    break;
                }
            }

            if (tile_available)
                break;
        }

        if (tile_available) {
            for (int count = 0; count < 1;) {
                int row = row_dist(engine);
                int col = col_dist(engine);

                if (tiles[row][col].State() == TileState::InBag) {
                    tiles[row][col].Pick(current_player_id);
                    count++;
                }
            }
        }

        // Switch to the next player
        current_player_id++;

        if (current_player_id > num_players) {
            current_player_id = 1;
        }

        // Select a tile from current player's hand
        bool tile_selected = false;
        for (int row = 0; row < tiles_up; row++) {
            for (int col = 0; col < tiles_across; col++) {
                if (tiles[row][col].OwnerID() == current_player_id) {
                    tiles[row][col].Select();
                    tile_selected = true;
                    break;
                }
            }

            if (tile_selected)
                break;
        }

        player_done = false;
    }

    if (switch_active_tile) {
        bool selected_tile_found = false;
        bool tile_selected = false;
        for (int row = 0; row < tiles_up; row++) {
            for (int col = 0; col < tiles_across; col++) {
                if (selected_tile_found && (tiles[row][col].OwnerID() == current_player_id)) {
                    tiles[row][col].Select();
                    tile_selected = true;
                    break;
                }

                if (tiles[row][col].State() == Selected) {
                    tiles[row][col].Deselect();
                    selected_tile_found = true;
                }
            }

            if (tile_selected)
                break;
        }

        if (!tile_selected) {
            for (int row = 0; row < tiles_up; row++) {
                for (int col = 0; col < tiles_across; col++) {
                    if (tiles[row][col].OwnerID() == current_player_id) {
                        tiles[row][col].Select();
                        tile_selected = true;
                        break;
                    }
                }

                if (tile_selected)
                    break;
            }
        }

        switch_active_tile = false;
    }
}

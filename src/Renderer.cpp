#include "Renderer.h"

#include <string>

Renderer::Renderer() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Acquire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::RenderBoard(Tile tiles[tiles_up][tiles_across]) {
    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const int divider_width = 3;
    const int tile_width = divider_width * 20;

    const int board_width = (tile_width * tiles_across) + (divider_width * (tiles_across + 1));
    const int board_height = (tile_width * tiles_up) + (divider_width * (tiles_up + 1));

    SDL_Rect board;
    board.w = board_width;
    board.h = board_height;
    board.x = (screen_width / 2) - (board.w / 2);
    board.y = (screen_height / 2) - (board.h / 2);

    SDL_SetRenderDrawColor(renderer, 0xEF, 0xED, 0xC0, SDL_ALPHA_OPAQUE);  // Dark cream
    SDL_RenderFillRect(renderer, &board);

    for (int row = 0; row < tiles_up; row++) {
        for (int col = 0; col < tiles_across; col++) {
            SDL_Rect tile;
            tile.w = tile.h = tile_width;
            tile.x = board.x + ((divider_width + tile_width) * col) + divider_width;
            tile.y = board.y + ((divider_width + tile_width) * row) + divider_width;

            switch (tiles[row][col].State()) {
                case TileState::Unplayed:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFD, 0xD0, SDL_ALPHA_OPAQUE);  // Cream
                    break;
                case TileState::Played:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);  // Black
                    break;
            }

            SDL_RenderFillRect(renderer, &tile);
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::RenderFPS(int fps) {
    std::string title{"Acquire (FPS: " + std::to_string(fps) + ")"};
    SDL_SetWindowTitle(window, title.c_str());
}

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

    for (int i = 0; i < tiles_up; i++) {
        for (int j = 0; j < tiles_across; j++) {
            SDL_Rect tile;
            tile.w = tile.h = tile_width;
            tile.x = board.x + ((divider_width + tile_width) * j) + divider_width;
            tile.y = board.y + ((divider_width + tile_width) * i) + divider_width;

            uint8_t r = tiles[i][j].owner->color.r;
            uint8_t g = tiles[i][j].owner->color.g;
            uint8_t b = tiles[i][j].owner->color.b;

            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &tile);
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::RenderFPS(int fps) {
    std::string title{"Acquire (FPS: " + std::to_string(fps) + ")"};
    SDL_SetWindowTitle(window, title.c_str());
}

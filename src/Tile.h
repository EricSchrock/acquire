#pragma once

constexpr std::size_t tiles_up{9};
constexpr std::size_t tiles_across{12};

enum TileState {
    Unplayed,
    Played,
};

class Tile {
public:
    TileState State() { return state; }

    void Place() { state = Played; }

private:
    TileState state{Unplayed};
};

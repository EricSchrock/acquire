#pragma once

#include "Player.h"

constexpr std::size_t tiles_up{9};
constexpr std::size_t tiles_across{12};

enum TileState {
    InBag,
    InHand,
    Placed,
};

class Tile {
public:
    TileState State() { return state; }
    Player* Owner() { return owner; }

    void Pick(Player* player) {
        state = InHand;
        owner = player;
    }

    void Place() {
        state = Placed;
        owner = nullptr;
    }

private:
    TileState state{InBag};
    Player* owner{nullptr};
};

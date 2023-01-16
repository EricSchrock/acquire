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
    unsigned int OwnerID() { return owner_id; }

    void Pick(unsigned int id) {
        state = InHand;
        owner_id = id;
    }

    void Place() {
        state = Placed;
        owner_id = 0;
    }

private:
    TileState state{InBag};
    unsigned int owner_id{0};
};

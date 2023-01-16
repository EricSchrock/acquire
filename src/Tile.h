#pragma once

#include "Entity.h"

static constexpr std::size_t tiles_up{9};
static constexpr std::size_t tiles_across{12};

class Tile {
public:
    Entity* owner;
};

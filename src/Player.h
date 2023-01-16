#pragma once

#include <string>

class Player {
public:
    Player(unsigned int id)
        : id(id) {
        name = "Player " + std::to_string(id);
    }

    std::string Name() { return name; }

private:
    unsigned int id;
    std::string name;
};

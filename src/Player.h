#pragma once

#include <string>

class Player {
public:
    Player(std::string name)
        : name(name) {}

    std::string Name() { return name; }

private:
    std::string name;
};

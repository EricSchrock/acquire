#include <iostream>

#include "Game.h"

int main() {
    unsigned int num_players;

    std::cout << "Number of players: ";
    std::cin >> num_players;

    Game game{num_players};

    game.Run();

    return 0;
}

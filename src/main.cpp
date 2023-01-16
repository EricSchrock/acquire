#include <iostream>
#include <random>
#include <thread>

#include "Game.h"
#include "Renderer.h"

int main() {
    Renderer renderer;
    Game game;

    game.Run(renderer);

    return 0;
}

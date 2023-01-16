#include <iostream>
#include <random>
#include <thread>

#include "Controller.h"
#include "Game.h"
#include "Renderer.h"

int main() {
    Controller controller;
    Renderer renderer;
    Game game;

    game.Run(controller, renderer);

    return 0;
}

# Acquire

[Acquire](https://boardgamegeek.com/boardgame/5/acquire) is an old board game where players build hotel chains, buy stock, and complete mergers. At the end of the game, the player with the most money wins. This initial project implements the board where players can place tiles (hotels). Hotel chains, stock purchases, and mergers are not yet implemented.

<img src="doc/acquire.gif"/>

The overall structure of this project is inspired by the [CppND-Capstone-Snake-Game](https://github.com/udacity/CppND-Capstone-Snake-Game) repo from [Udacity](https://www.udacity.com/).


## Dependencies
* `clang-format` == 10.0.0
* `cmake` >= 3.7
* `gcc`/`g++` >= 5.4
* `make` >= 4.1
* SDL2 >= 2.0


## Building and running

1. Clone this repo
2. Run `make` to build and run the application
3. Enter the number of players on the command line
4. Use the `space` key to cycle through a player's tiles
5. Use the `enter` key to place the selected tile and transition to the next player


## Code structure

### Control flow
![Alt Text](doc/control-flow.png?raw=true)

### Class structure
![Alt Text](doc/class-diagram.png?raw=true)

### Tile state machine
![Alt Text](doc/tile-state-machine.png?raw=true)

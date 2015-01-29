#include <iostream>

#include <SFML/Window.hpp>

#include "game.hpp"

using namespace std;

int main(/*int argc, char* argv[]*/) {
    Game game;

    while(game.isOpen())
        game.loop();

    return 0;
}

#include "game.h"

#include <SFML/Window.hpp>

#include <iostream>

using namespace std;

int main(/*int argc, char* argv[]*/)
{
    Game game;

    while (game.isOpen())
        game.loop();

    return 0;
}

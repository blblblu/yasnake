#include "game.h"

#include <SFML/Window.hpp>

#include <iostream>

using namespace std;

int main()
{
    Game game;

    while (game.isOpen())
    {
        game.loop();
    }

    return 0;
}

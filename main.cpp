#include <iostream>

#include <SFML/Window.hpp>

#include "game.h"
#include "introstate.h"
#include "matchstate.h"

using namespace std;

int main(int argc, char* argv[]) {
    Game game(sf::VideoMode(800, 600), "TowerDefense");

    while(game.isOpen())
        game.loop();

    return 0;
}

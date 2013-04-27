#include <iostream>

#include <SFML/Window.hpp>

#include "game.h"

using namespace std;

int main(int argc, char* argv[]) {
    Game game(sf::VideoMode(1280, 720), "TowerDefense");

    while(game.isOpen())
        game.loop();

    return 0;
}

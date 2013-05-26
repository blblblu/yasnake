#include <iostream>

#include <SFML/Window.hpp>

#include "game.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Game game(sf::VideoMode(1280, 720), "Snake");

    while(game.isOpen())
        game.loop();

    return 0;
}

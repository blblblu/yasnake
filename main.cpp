#include <iostream>

#include <SFML/Window.hpp>

#include "game.h"
#include "introstate.h"
#include "matchstate.h"

using namespace std;

int main(int argc, char* argv[]) {
    Game game(sf::VideoMode(800, 600), "TowerDefense");

    // vorhandene Gamestates dem Statemanager bekanntmachen
    game.stateManager.addState("IntroState", new IntroState());
    game.stateManager.addState("MatchState", new MatchState());

    game.stateManager.changeState("IntroState", game.window);

    while(game.isOpen())
    {
        game.handleEvents();
        game.update();
        game.draw();
    }

    return 0;
}

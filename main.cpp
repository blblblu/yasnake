#include <iostream>

#include <SFML/Window.hpp>

#include "gameengine.h"
#include "introstate.h"
#include "matchstate.h"

using namespace std;

int main(int argc, char* argv[]) {
    GameEngine game(sf::VideoMode(800, 600), "TowerDefense");

    // vorhandene Gamestates dem Statemanager bekanntmachen
    game.addState("IntroState", new IntroState());
    game.addState("MatchState", new MatchState());

    game.changeState("IntroState");

    while(game.isOpen())
    {
        game.handleEvents();
        game.update();
        game.draw();
    }

    return 0;
}

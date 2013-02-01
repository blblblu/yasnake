#include "gameengine.h"
#include "introstate.h"

#include <iostream>
#include <SFML/Window.hpp>

using namespace std;

int main(int argc, char* argv[]) {
  GameEngine game(sf::VideoMode(800, 600), "TowerDefense");

  game.changeState(new IntroState());

  while(game.running())
  {
      game.handleEvents();
      game.update();
      game.draw();
  }

  return 0;
}

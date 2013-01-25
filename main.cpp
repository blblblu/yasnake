#include "gameengine.h"

#include <iostream>
#include <SFML/Window.hpp>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Hello World"<< endl;

  GameEngine game(sf::VideoMode(800, 600), "TowerDefense");

  while(game.running()){
      game.handleEvents();
      game.update();
      game.draw();
  }

  return 0;
}

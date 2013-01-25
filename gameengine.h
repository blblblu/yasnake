#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Window.hpp>

#include "gamestate.h"

using namespace std;

class GameEngine
{
public:
    GameEngine(sf::VideoMode videoMode, const string &title);
    ~GameEngine();

    void changeState(GameState* state);
    void pushState(GameState* state);
    void popState();

    void handleEvents();
    void update();
    void draw();

    bool running(){return _running;}
    void quit(){_running = false;}

    sf::Window* window;

private:
    vector<GameState*> states;

    bool _running;
};

#endif // GAMEENGINE_H

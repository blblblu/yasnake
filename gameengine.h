#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gamestate.h"

using namespace std;

class GameState;

class GameEngine
{
public:
    GameEngine(sf::VideoMode videoMode, const string &title);
    ~GameEngine();

    void changeState(GameState *state);
    void pushState(GameState *state);
    void popState();

    void handleEvents();
    void update();
    void draw();

    bool running();
    void quit();

    sf::RenderWindow* window;

private:
    vector< shared_ptr<GameState> > _states;
};

#endif // GAMEENGINE_H

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gamestate.h"

class GameState;

class GameEngine
{
public:
    GameEngine(sf::VideoMode videoMode, const std::string &title);
    ~GameEngine();

    void changeState(GameState *state);
    void pushState(GameState *state);
    void popState();

    void handleEvents();
    void update();
    void draw();

    bool running();
    void quit();

    sf::View view;
    sf::RenderWindow window;

private:
    std::vector< std::shared_ptr<GameState> > _states;
};

#endif // GAMEENGINE_H

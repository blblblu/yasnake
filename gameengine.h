#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <exception>
#include <iostream>
#include <map>
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

    void addState(const std::string &id, GameState *state);

    void changeState(const std::string id);
    void pushState(const std::string id);
    void popState();

    void handleEvents();
    void update();
    void draw();

    bool isOpen();
    void close();
    void create(sf::VideoMode videoMode, const std::string &title);

    sf::View view;
    sf::RenderWindow window;

private:
    std::map<std::string, std::shared_ptr<GameState> > _statesById;
    std::vector<std::shared_ptr<GameState> > _activeStates;
};

#endif // GAMEENGINE_H

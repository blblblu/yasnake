#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gamestate.h"

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void addState(const std::string &id, GameState *state);

    void changeState(const std::string id, sf::RenderWindow &window);
    void pushState(const std::string id, sf::RenderWindow &window);
    void popState(sf::RenderWindow &window);

    std::shared_ptr<GameState> back();

private:
    std::map<std::string, std::shared_ptr<GameState> > _statesById;
    std::vector<std::shared_ptr<GameState> > _activeStates;
};

#endif // STATEMANAGER_H

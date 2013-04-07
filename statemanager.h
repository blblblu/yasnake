#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "debugoutput.h"
#include "gamestate.h"

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void addState(const std::string &id, GameState *state);

    void replaceState(const std::string id);
    void pushState(const std::string id);
    void popState();

    GameState* backActive();
    bool emptyActive();

private:
    std::map<std::string, std::unique_ptr<GameState> > _statesById;
    std::vector<GameState*> _activeStates;
};

#endif // STATEMANAGER_H

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "debugoutput.hpp"
#include "gamestate.hpp"

class GameState;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void addState(const std::string &id, GameState *state);

    void replaceState(const std::string id);
    void pushState(const std::string id);
    void popState();

    GameState *backActive();
    GameState *getState(const std::string &id);
    bool emptyActive();

private:
    std::map<std::string, std::unique_ptr<GameState> > m_statesById;
    std::vector<GameState*> m_activeStates;
};

#endif // STATEMANAGER_H

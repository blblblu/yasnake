#pragma once

#include <states/gamestate.h>

#include <memory>
#include <stack>

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
    std::map<std::string, std::unique_ptr<GameState>> m_statesById;
    std::stack<GameState *> m_activeStates;
};

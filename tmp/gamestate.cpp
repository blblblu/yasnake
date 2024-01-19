#include "gamestate.h"

GameState::GameState()
{
    this->m_isActive = false;
    this->m_isPaused = false;
}

bool GameState::isActive()
{
    return this->m_isActive;
}

bool GameState::isPaused()
{
    return this->m_isPaused;
}

bool GameState::pollStateEvent(StateEvent &stateEvent)
{
    if(!this->m_stateEvents.empty())
    {
        stateEvent = this->m_stateEvents.front();
        this->m_stateEvents.pop();
        return true;
    }
    else
        return false;
}

void GameState::addStateEvent(const StateEvent &stateEvent)
{
    this->m_stateEvents.push(stateEvent);
}

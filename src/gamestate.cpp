#include "gamestate.h"

GameState::GameState()
{
    m_isActive = false;
    m_isPaused = false;
}

bool GameState::isActive()
{
    return m_isActive;
}

bool GameState::isPaused()
{
    return m_isPaused;
}

bool GameState::pollStateEvent(StateEvent &stateEvent)
{
    if(!m_stateEvents.empty())
    {
        stateEvent = m_stateEvents.front();
        m_stateEvents.pop();
        return true;
    }
    else
        return false;
}

void GameState::addStateEvent(const StateEvent &stateEvent)
{
    m_stateEvents.push(stateEvent);
}

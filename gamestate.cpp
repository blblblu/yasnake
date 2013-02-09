#include "gamestate.h"

GameState::GameState(sf::RenderTarget *renderTarget)
{
    this->_isActive = false;
    this->_isPaused = false;

    this->_stateChangeType = StateChangeType::None;

    this->_renderTarget = renderTarget;
}

bool GameState::isActive()
{
    return this->_isActive;
}

bool GameState::isPaused()
{
    return this->_isPaused;
}

bool GameState::stateChange(int &stateChangeType, std::string &nextState)
{
    if(this->_stateChangeType == StateChangeType::None)
    {
        return false;
    }
    else
    {
        stateChangeType = this->_stateChangeType;
        nextState = this->_nextState;

        this->_stateChangeType = StateChangeType::None;

        return true;
    }
}

void GameState::changeState(const unsigned int stateChangeType, const std::string &nextState)
{
    // Überprüfung, ob stateChangeType ein korrekter StateChangeType-Wert ist und ggf. Exception werfen
    if(stateChangeType >= StateChangeType::LAST)
        throw std::exception();

    this->_stateChangeType = stateChangeType;
    this->_nextState = nextState;
}


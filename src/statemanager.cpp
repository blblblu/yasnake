#include "statemanager.h"

#include <debugoutput.h>

StateManager::StateManager()
{
    DebugOutput::stateManager("initialization");
}

StateManager::~StateManager()
{
    DebugOutput::stateManager("cleanup");

    // alle Gamestates löschen und entfernen
    while(!m_activeStates.empty())
    {
        m_activeStates.top()->stop();
        m_activeStates.top()->m_isActive = false;
        m_activeStates.pop();
    }
}

void StateManager::addState(const std::string &id, GameState *state)
{
    DebugOutput::stateManager("addState");

    if(id.length() ==  0)
        throw std::runtime_error("Id must not be an empty string");
    if(state == nullptr)
        throw std::runtime_error("Gamestate must not be NULL");

    std::map<std::string, std::unique_ptr<GameState> >::iterator it = m_statesById.find(id);
    if(it != m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" already exists");
        throw std::runtime_error(error);
    }

    m_statesById[id] = std::unique_ptr<GameState>(state);

    DebugOutput::stateManager("state \"" + id + "\" added");
}

void StateManager::replaceState(const std::string id)
{
    DebugOutput::stateManager("changeState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!m_activeStates.empty())
    {
        m_activeStates.top()->stop();
        m_activeStates.top()->m_isActive = false;
        m_activeStates.pop();
    }

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = m_statesById.find(id);
    if(it == m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    m_activeStates.push(m_statesById[id].get());

    // neuen Gamestate starten
    m_activeStates.top()->start();
    m_activeStates.top()->m_isActive = true;

    DebugOutput::stateManager("changed active state to state \"" + id + "\"");
}

void StateManager::pushState(const std::string id)
{
    DebugOutput::stateManager("pushState");

    // derzeitigen Gamestate pausieren
    if(!m_activeStates.empty())
    {
        m_activeStates.top()->pause();
        m_activeStates.top()->m_isPaused = true;
    }

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = m_statesById.find(id);
    if(it == m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    m_activeStates.push(m_statesById[id].get());

    // neuen Gamestate starten
    m_activeStates.top()->start();
    m_activeStates.top()->m_isActive = true;

    DebugOutput::stateManager("added state \"" + id + "\" as active state");
}

void StateManager::popState()
{
    DebugOutput::stateManager("popState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!m_activeStates.empty())
    {
        m_activeStates.top()->stop();
        m_activeStates.top()->m_isActive = false;
        m_activeStates.pop();
    }

    // vorherigen Gamestate weiterführen
    if(!m_activeStates.empty())
    {
        m_activeStates.top()->resume();
        m_activeStates.top()->m_isPaused = false;
    }
}

GameState *StateManager::backActive()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(m_activeStates.empty())
        throw std::runtime_error("Vector of active Gamestates is empty");

    return m_activeStates.top();
}

GameState *StateManager::getState(const std::string &id)
{
    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = m_statesById.find(id);
    if(it == m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    return m_statesById[id].get();
}

bool StateManager::emptyActive()
{
    return m_activeStates.empty();
}

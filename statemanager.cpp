#include "statemanager.h"

StateManager::StateManager()
{
    DebugOutput::stateManager("initialization");
}

StateManager::~StateManager()
{
    DebugOutput::stateManager("cleanup");

    // alle Gamestates löschen und entfernen
    while(!this->m_activeStates.empty())
    {
        this->m_activeStates.back()->stop();
        this->m_activeStates.pop_back();
    }
}

void StateManager::addState(const std::string &id, GameState *state)
{
    DebugOutput::stateManager("addState");

    if(id.length() ==  0)
        throw std::runtime_error("Id must not be an empty string");
    if(state == nullptr)
        throw std::runtime_error("Gamestate must not be NULL");

    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->m_statesById.find(id);
    if(it != this->m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" already exists");
        throw std::runtime_error(error);
    }

    this->m_statesById[id] = std::unique_ptr<GameState>(state);

    DebugOutput::stateManager("state \"" + id + "\" added");
}

void StateManager::replaceState(const std::string id)
{
    DebugOutput::stateManager("changeState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!this->m_activeStates.empty())
    {
        this->m_activeStates.back()->stop();
        this->m_activeStates.pop_back();
    }

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->m_statesById.find(id);
    if(it == this->m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    this->m_activeStates.push_back(this->m_statesById[id].get());

    // neuen Gamestate starten
    this->m_activeStates.back()->start();

    DebugOutput::stateManager("changed active state to state \"" + id + "\"");
}

void StateManager::pushState(const std::string id)
{
    DebugOutput::stateManager("pushState");

    // derzeitigen Gamestate pausieren
    if(!this->m_activeStates.empty())
        this->m_activeStates.back()->pause();

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->m_statesById.find(id);
    if(it == this->m_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    this->m_activeStates.push_back(this->m_statesById[id].get());

    // neuen Gamestate starten
    this->m_activeStates.back()->start();

    DebugOutput::stateManager("added state \"" + id + "\" as active state");
}

void StateManager::popState()
{
    DebugOutput::stateManager("popState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!this->m_activeStates.empty())
    {
        this->m_activeStates.back()->stop();
        this->m_activeStates.pop_back();
    }

    // vorherigen Gamestate weiterführen
    if(!this->m_activeStates.empty())
    {
        this->m_activeStates.back()->resume();
    }
}

GameState *StateManager::backActive()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->m_activeStates.empty())
        throw std::runtime_error("Vector of active Gamestates is empty");

    return this->m_activeStates.back();
}

bool StateManager::emptyActive()
{
    return this->m_activeStates.empty();
}

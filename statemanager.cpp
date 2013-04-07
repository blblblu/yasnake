#include "statemanager.h"

StateManager::StateManager()
{
    DebugOutput::stateManager("initialization");
}

StateManager::~StateManager()
{
    DebugOutput::stateManager("cleanup");

    // alle Gamestates löschen und entfernen
    while(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }
}

void StateManager::addState(const std::string &id, GameState *state)
{
    DebugOutput::stateManager("addState");

    if(id.length() ==  0)
        throw std::runtime_error("Id must not be an empty string");
    if(state == nullptr)
        throw std::runtime_error("Gamestate must not be NULL");

    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it != this->_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" already exists");
        throw std::runtime_error(error);
    }

    this->_statesById[id] = std::unique_ptr<GameState>(state);

    DebugOutput::stateManager("state \"" + id + "\" added");
}

void StateManager::replaceState(const std::string id)
{
    DebugOutput::stateManager("changeState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it == this->_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    this->_activeStates.push_back(this->_statesById[id].get());

    // neuen Gamestate starten
    this->_activeStates.back()->start();

    DebugOutput::stateManager("changed active state to state \"" + id + "\"");
}

void StateManager::pushState(const std::string id)
{
    DebugOutput::stateManager("pushState");

    // derzeitigen Gamestate pausieren
    if(!this->_activeStates.empty())
        this->_activeStates.back()->pause();

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::unique_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it == this->_statesById.end())
    {
        std::string error;
        error.append("Gamestate with id \"");
        error.append(id);
        error.append("\" does not exist");
        throw std::runtime_error(error);
    }

    // neuen Gamestate einfügen
    this->_activeStates.push_back(this->_statesById[id].get());

    // neuen Gamestate starten
    this->_activeStates.back()->start();

    DebugOutput::stateManager("added state \"" + id + "\" as active state");
}

void StateManager::popState()
{
    DebugOutput::stateManager("popState");

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }

    // vorherigen Gamestate weiterführen
    if(!this->_activeStates.empty())
    {
        this->_activeStates.back()->resume();
    }
}

GameState *StateManager::backActive()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->_activeStates.empty())
        throw std::runtime_error("Vector of active Gamestates is empty");

    return this->_activeStates.back();
}

bool StateManager::emptyActive()
{
    return this->_activeStates.empty();
}

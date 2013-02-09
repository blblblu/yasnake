#include "statemanager.h"

StateManager::StateManager()
{
    std::cout << "[StateManager] initialization" << std::endl;
}

StateManager::~StateManager()
{
    std::cout << "[StateManager] cleanup" << std::endl;

    // alle Gamestates löschen und entfernen
    while(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }
}

void StateManager::addState(const std::string &id, GameState *state)
{
    std::cout << "[StateManager] addState" << std::endl;

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

    std::cout << "[StateManager] state \"" << id << "\" added" << std::endl;
}

void StateManager::replaceState(const std::string id)
{
    std::cout << "[StateManager] changeState" << std::endl;

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

    std::cout << "[StateManager] changed active state to state \"" << id << "\"" << std::endl;
}

void StateManager::pushState(const std::string id)
{
    std::cout << "[StateManager] pushState" << std::endl;

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

    std::cout << "[StateManager] added state \"" << id << "\" as active state" << std::endl;
}

void StateManager::popState()
{
    std::cout << "[StateManager] popState" << std::endl;

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

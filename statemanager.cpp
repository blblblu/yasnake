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
        throw std::exception(); // TODO
    if(state == nullptr)
        throw std::exception(); // TODO

    std::map<std::string, std::shared_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it != this->_statesById.end())
        throw std::exception(); // TODO

    this->_statesById[id] = std::shared_ptr<GameState>(state);

    std::cout << "[StateManager] state \"" << id << "\" added" << std::endl;
}

void StateManager::changeState(const std::string id, sf::RenderWindow &window)
{
    std::cout << "[StateManager] changeState" << std::endl;

    // derzeitigen Gamestate aus Liste der aktiven Gamestates entfernen
    if(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::shared_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it == this->_statesById.end())
        throw std::exception();

    // neuen Gamestate einfügen
    this->_activeStates.push_back(this->_statesById[id]);

    // neuen Gamestate starten
    this->_activeStates.back()->start(window);

    std::cout << "[StateManager] changed active state to state \"" << id << "\"" << std::endl;
}

void StateManager::pushState(const std::string id, sf::RenderWindow &window)
{
    std::cout << "[StateManager] pushState" << std::endl;

    // derzeitigen Gamestate pausieren
    if(!this->_activeStates.empty())
        this->_activeStates.back()->pause(window);

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::shared_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it == this->_statesById.end())
        throw std::exception();

    // neuen Gamestate einfügen
    this->_activeStates.push_back(this->_statesById[id]);

    // neuen Gamestate starten
    this->_activeStates.back()->start(window);

    std::cout << "[StateManager] added state \"" << id << "\" as active state" << std::endl;
}

void StateManager::popState(sf::RenderWindow &window)
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
        this->_activeStates.back()->resume(window);
    }
}

std::shared_ptr<GameState> StateManager::back()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->_activeStates.empty())
        throw std::exception(); // TODO

    return this->_activeStates.back();
}

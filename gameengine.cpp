#include "gameengine.h"

GameEngine::GameEngine(sf::VideoMode videoMode, const std::string &title) : view(sf::FloatRect(0, 0, 800, 600))
{
    std::cout << "[GameEngine] initialization" << std::endl;
    this->create(videoMode, title);
}
GameEngine::~GameEngine()
{
    std::cout << "[GameEngine] cleanup" << std::endl;

    // alle GameStates löschen und entfernen
    while(!this->_activeStates.empty())
    {
        this->_activeStates.back()->stop();
        this->_activeStates.pop_back();
    }
}

void GameEngine::addState(const std::string &id, GameState *state)
{
    std::cout << "[GameEngine] addState" << std::endl;

    if(id.length() ==  0)
        throw std::exception(); // TODO
    if(state == nullptr)
        throw std::exception(); // TODO

    std::map<std::string, std::shared_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it != this->_statesById.end())
        throw std::exception(); // TODO

    this->_statesById[id] = std::shared_ptr<GameState>(state);

    std::cout << "[GameEngine] state \"" << id << "\" added" << std::endl;
}

void GameEngine::changeState(const std::string id)
{
    std::cout << "[GameEngine] changeState" << std::endl;

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
    this->_activeStates.back()->start();

    // View vom neuen Gamestate zurücksetzen lassen
    this->_activeStates.back()->resize(this);

    std::cout << "[GameEngine] changed active state to state \"" << id << "\"" << std::endl;
}

void GameEngine::pushState(const std::string id)
{
    std::cout << "[GameEngine] pushState" << std::endl;

    // derzeitigen Gamestate pausieren
    if(!this->_activeStates.empty())
        this->_activeStates.back()->pause();

    // prüfen, ob Gamestate mit id überhaupt existiert (und ggf. Exception werfen)
    std::map<std::string, std::shared_ptr<GameState> >::iterator it = this->_statesById.find(id);
    if(it == this->_statesById.end())
        throw std::exception();

    // neuen Gamestate einfügen
    this->_activeStates.push_back(this->_statesById[id]);

    // neuen Gamestate starten
    this->_activeStates.back()->start();

    // View vom neuen Gamestate zurücksetzen lassen
    this->_activeStates.back()->resize(this);

    std::cout << "[GameEngine] added state \"" << id << "\" as active state" << std::endl;
}

void GameEngine::popState()
{
    std::cout << "[GameEngine] popState" << std::endl;

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

        // View vom vorherigen Gamestate zurücksetzen lassen
        this->_activeStates.back()->resize(this);
    }
}

void GameEngine::handleEvents()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->_activeStates.empty())
        throw std::exception(); // TODO

    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            this->window.close();
        if(event.type == sf::Event::Resized)
            this->_activeStates.back()->resize(this);

        this->_activeStates.back()->handleEvent(this, &event);
    }
}

void GameEngine::update()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->_activeStates.empty())
        throw std::exception(); // TODO

    this->_activeStates.back()->update(this);
}

void GameEngine::draw()
{
    // prüfen, ob Liste der aktiven Gamestates leer ist und ggf. Exception werfen
    if(this->_activeStates.empty())
        throw std::exception(); // TODO

    this->window.clear(sf::Color(0,0,0));
    this->_activeStates.back()->draw(this, &this->window);
    this->window.display();
}

bool GameEngine::isOpen()
{
    return this->window.isOpen();
}

void GameEngine::close()
{
    this->window.close();
}

void GameEngine::create(sf::VideoMode videoMode, const std::string &title)
{
    std::cout << "[GameEngine] create" << std::endl;

    this->window.create(videoMode, title);
    this->window.setView(this->view);
}

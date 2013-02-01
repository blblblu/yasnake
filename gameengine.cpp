#include "gameengine.h"

GameEngine::GameEngine(sf::VideoMode videoMode, const std::string &title) : view(sf::Vector2f(400, 300), sf::Vector2f(800, 600)), window(videoMode, title)
{
    this->window.setView(this->view);

    std::cout << "[GameEngine] Initialization" << std::endl;
}

GameEngine::~GameEngine()
{
    // alle GameStates löschen und entfernen
    while(!this->_states.empty())
    {
        this->_states.pop_back();
    }

    std::cout << "[GameEngine] Cleanup" << std::endl;
}

void GameEngine::changeState(GameState *state)
{
    // derzeitigen Gamestate entfernen
    if(!this->_states.empty())
    {
        this->_states.pop_back();
    }

    // neuen Gamestate einfügen
    this->_states.push_back(std::shared_ptr<GameState>(state));
}

void GameEngine::pushState(GameState *state)
{
    // derzeitigen GameState pausieren
    if(!this->_states.empty())
    {
        this->_states.back()->pause();
    }

    // neuen Gamestate einfügen
    this->_states.push_back(std::shared_ptr<GameState>(state));
}

void GameEngine::popState()
{
    // derzeitigen GameState entfernen
    if(!this->_states.empty())
    {
        this->_states.pop_back();
    }

    // vorherigen GameState weiterführen
    if(!this->_states.empty())
    {
        this->_states.back()->resume();
    }
}

void GameEngine::handleEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window.close();
        this->_states.back()->handleEvent(this, &event);
    }
}

void GameEngine::update()
{
    this->_states.back()->update(this);
}

void GameEngine::draw()
{
    this->window.clear(sf::Color(0,0,0));
    this->_states.back()->draw(this);
    this->window.display();
}

bool GameEngine::running()
{
    return this->window.isOpen();
}

void GameEngine::quit()
{
    this->window.close();
}

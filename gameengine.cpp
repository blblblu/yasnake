#include "gameengine.h"

GameEngine::GameEngine(sf::VideoMode videoMode, const string &title)
{
    // SFML-Fenster erstellen
    this->window = new sf::Window(videoMode, title);
    this->_running = true;

    cout << "GameEngine - Initialization" << endl;
}

GameEngine::~GameEngine()
{
    // alle GameStates löschen und entfernen
    while(!this->states.empty())
    {
        delete this->states.back();
        this->states.back() = NULL;
        this->states.pop_back();
    }

    cout << "GameEngine - Cleanup" << endl;
}

void GameEngine::changeState(GameState *state)
{
    // derzeitigen Gamestate entfernen
    if(!this->states.empty())
    {
        delete this->states.back();
        this->states.back() = NULL;
        this->states.pop_back();
    }

    // neuen Gamestate einfügen
    this->states.push_back(state);
}

void GameEngine::pushState(GameState *state)
{
    // derzeitigen GameState pausieren
    if(!this->states.empty())
    {
        this->states.back()->pause();
    }

    // neuen Gamestate einfügen
    this->states.push_back(state);
}

void GameEngine::popState()
{
    // derzeitigen GameState entfernen
    if(!this->states.empty())
    {
        delete this->states.back();
        this->states.back() = NULL;
        this->states.pop_back();
    }

    // vorherigen GameState weiterführen
    if(!this->states.empty())
    {
        this->states.back()->resume();
    }
}

void GameEngine::handleEvents()
{
    this->states.back()->handleEvents(this);
}

void GameEngine::update()
{
    this->states.back()->update(this);
}

void GameEngine::draw()
{
    this->states.back()->draw(this);
}

#include "game.h"

Game::Game(sf::VideoMode videoMode, const std::string &title)
{
    DebugOutput::game("initialization");
    this->create(videoMode, title);

    // vorhandene Gamestates dem Statemanager bekanntmachen
    this->m_stateManager.addState("MenuState", new MenuState());
    this->m_stateManager.addState("MatchState", new MatchState());

    // Hauptmenü laden
    this->m_stateManager.pushState("MenuState");
}

Game::~Game()
{
    DebugOutput::game("cleanup");
}

void Game::create(sf::VideoMode videoMode, const std::string &title)
{
    DebugOutput::game("create");

    this->m_window.create(videoMode, title);
}

void Game::close()
{
    DebugOutput::game("close");
    this->m_window.close();
}

void Game::loop()
{
    // Fenster schließen, wenn kein GameState mehr aktiv ist
    if(this->m_stateManager.emptyActive())
        this->close();
    else
    {
        // TODO: Reihenfolge berichtigen
        this->handleEvents();
        this->update();
        this->draw();
        this->handleStateEvents();
    }
}

bool Game::isOpen()
{
    return this->m_window.isOpen();
}

void Game::handleStateEvents()
{
    StateEvent stateEvent;
    while(this->m_stateManager.backActive()->pollStateEvent(stateEvent))
    {
        switch(stateEvent.type)
        {
        case StateEvent::ReplaceState:
            this->m_stateManager.replaceState(boost::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        case StateEvent::PushState:
            this->m_stateManager.pushState(boost::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        case StateEvent::PopState:
            this->m_stateManager.popState();
            // View zurücksetzen
            if(!this->m_stateManager.emptyActive())
                this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        }
        // Automatisch aufhören, sobald kein GameState mehr aktiv ist
        if(this->m_stateManager.emptyActive())
            break;
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (this->m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            this->m_window.close();
        if(event.type == sf::Event::Resized)
            this->m_window.setView(this->m_stateManager.backActive()->resize(event.size.width, event.size.height));

        this->m_stateManager.backActive()->handleEvent(event);
    }
}

void Game::update()
{
    this->m_stateManager.backActive()->update();
}

void Game::draw()
{
    this->m_window.clear(sf::Color(0, 0, 0));
    this->m_stateManager.backActive()->draw(this->m_window);
    this->m_window.display();
}

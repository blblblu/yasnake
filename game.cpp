#include "game.h"

Game::Game(sf::VideoMode videoMode, const std::string &title)
{
    DebugOutput::game("initialization");
    this->create(videoMode, title);

    // vorhandene Gamestates dem Statemanager bekanntmachen
    this->_stateManager.addState("IntroState", new MenuState(&this->window));
    this->_stateManager.addState("MatchState", new MatchState(&this->window));
    this->_stateManager.pushState("IntroState");

//    this->music.openFromFile("14 - ui.flac");
//    this->music.setLoop(true);
//    this->music.play();
}

Game::~Game()
{
    DebugOutput::game("cleanup");
}

void Game::create(sf::VideoMode videoMode, const std::string &title)
{
    DebugOutput::game("create");

    this->window.create(videoMode, title);
}

void Game::close()
{
    DebugOutput::game("close");
    this->window.close();
}

void Game::loop()
{
    // Fenster schließen, wenn kein GameState mehr aktiv ist
    if(this->_stateManager.emptyActive())
        this->close();
    else
    {
        this->handleEvents();
        this->update();
        this->draw();
        this->handleStateChange();
    }
}

void Game::handleStateChange()
{
    int stateChangeType = StateChangeType::None;
    std::string nextState = "";
    if(this->_stateManager.backActive()->stateChange(stateChangeType, nextState))
    {
        switch(stateChangeType)
        {
        case StateChangeType::ReplaceState:
            this->_stateManager.replaceState(nextState);
            // View zurücksetzen
            this->window.setView(this->_stateManager.backActive()->resize(this->window.getSize().x, this->window.getSize().y));
            break;
        case StateChangeType::PushState:
            this->_stateManager.pushState(nextState);
            // View zurücksetzen
            this->window.setView(this->_stateManager.backActive()->resize(this->window.getSize().x, this->window.getSize().y));
            break;
        case StateChangeType::PopState:
            this->_stateManager.popState();
            // View zurücksetzen
            if(!this->_stateManager.emptyActive())
                this->window.setView(this->_stateManager.backActive()->resize(this->window.getSize().x, this->window.getSize().y));
            break;
        }
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            this->window.close();
        if(event.type == sf::Event::Resized)
            this->window.setView(this->_stateManager.backActive()->resize(event.size.width, event.size.height));

        this->_stateManager.backActive()->handleEvent(event);
    }
}

void Game::update()
{
    this->_stateManager.backActive()->update();
}

void Game::draw()
{
    this->window.clear(sf::Color(0, 0, 0));
    this->_stateManager.backActive()->draw(this->window);
    this->window.display();
}

bool Game::isOpen()
{
    return this->window.isOpen();
}

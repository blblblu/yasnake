#include "game.h"

Game::Game(sf::VideoMode videoMode, const std::string &title)
{
    std::cout << "[Game] initialization" << std::endl;
    this->create(videoMode, title);
}

Game::~Game()
{
    std::cout << "[Game] cleanup" << std::endl;
}

void Game::create(sf::VideoMode videoMode, const std::string &title)
{
    std::cout << "[Game] create" << std::endl;

    this->window.create(videoMode, title);
}

void Game::handleEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            this->window.close();
        if(event.type == sf::Event::Resized)
            this->stateManager.back()->resize(this->window);

        this->stateManager.back()->handleEvent(this, event);
    }
}

void Game::update()
{
    this->stateManager.back()->update(this);
}

void Game::draw()
{
    this->window.clear(sf::Color(0,0,0));
    this->stateManager.back()->draw(this->window);
    this->window.display();
}

bool Game::isOpen()
{
    return this->window.isOpen();
}

void Game::close()
{
    this->window.close();
}

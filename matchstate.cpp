#include "matchstate.h"

MatchState::MatchState()
{
    std::cout << "[MatchState] initialization" << std::endl;
}

MatchState::~MatchState()
{
    std::cout << "[MatchState] cleanup" << std::endl;
}

void MatchState::start(sf::RenderWindow &window)
{
    std::cout << "[MatchState] start" << std::endl;

    this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(700, 400)));
    this->_field->setFillColor(sf::Color(238, 232, 213));
    this->_field->setOutlineColor(sf::Color(181, 137, 0));
    this->_field->setOutlineThickness(2);

    this->_isActive = true;

    // View zurücksetzen
    this->resize(window);
}

void MatchState::stop()
{
    std::cout << "[MatchState] stop" << std::endl;

    this->_field = nullptr;

    this->_isActive = false;
}

void MatchState::pause(sf::RenderWindow &window)
{
    std::cout << "[MatchState] pause" << std::endl;

    this->_isPaused = true;
}

void MatchState::resume(sf::RenderWindow &window)
{
    std::cout << "[MatchState] resume" << std::endl;

    this->_isPaused = false;

    // View zurücksetzen lassen
    this->resize(window);
}

void MatchState::handleEvent(Game *game, const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Q)
            game->stateManager.popState(game->window);
        break;
    }
}

void MatchState::resize(sf::RenderWindow &window)
{
    window.setView(sf::View(sf::Vector2f(350, 200), sf::Vector2f(window.getSize().x, window.getSize().y)));
}

void MatchState::update(Game *game)
{
}

void MatchState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->_field);
}

#include "matchstate.h"

MatchState::MatchState()
{
    std::cout << "[MatchState] initialization" << std::endl;
}

MatchState::~MatchState()
{
    std::cout << "[MatchState] cleanup" << std::endl;
}

void MatchState::start()
{
    std::cout << "[MatchState] start" << std::endl;
}

void MatchState::stop()
{
    std::cout << "[MatchState] stop" << std::endl;
}

void MatchState::pause()
{
    std::cout << "[MatchState] pause" << std::endl;
}

void MatchState::resume()
{
    std::cout << "[MatchState] resume" << std::endl;
}

void MatchState::handleEvent(GameEngine *game, sf::Event *event)
{
    switch(event->type)
    {
    case sf::Event::KeyPressed:
        if(event->key.code == sf::Keyboard::Q)
            game->popState();
        break;
    }
}

void MatchState::resize(GameEngine *game)
{
    game->view.setSize(game->window.getSize().x, game->window.getSize().y);
    game->view.setCenter(350, 200);
    game->window.setView(game->view);
}

void MatchState::update(GameEngine *game)
{
}

void MatchState::draw(GameEngine *game, sf::RenderTarget *renderTarget)
{
    renderTarget->clear(sf::Color(253, 246, 227));
    renderTarget->draw(sf::RectangleShape(sf::Vector2f(700, 400)));
}

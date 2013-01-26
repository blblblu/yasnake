#include "introstate.h"

IntroState::IntroState()
{
    // TODO Fehlerabfrage
    this->_texture = shared_ptr<sf::Texture>(new sf::Texture());
    this->_texture->loadFromFile("intro.png");

    this->_sprite = shared_ptr<sf::Sprite>(new sf::Sprite(*this->_texture));
}

IntroState::~IntroState()
{
}

void IntroState::pause()
{
}

void IntroState::resume()
{
}

void IntroState::handleEvent(GameEngine *game, sf::Event *event)
{
    switch(event->type)
    {
    case sf::Event::KeyPressed:
        if(event->key.code == sf::Keyboard::Q)
            game->quit();
        break;
    }
}

void IntroState::update(GameEngine *game)
{
}

void IntroState::draw(GameEngine *game)
{
    game->window->draw(*this->_sprite);
}

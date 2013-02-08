#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
    GameState(){}
    virtual ~GameState(){}

    virtual void start(sf::RenderWindow &window) = 0;
    virtual void stop() = 0;

    virtual void pause(sf::RenderWindow &window) = 0;
    virtual void resume(sf::RenderWindow &window) = 0;

    virtual void handleEvent(Game *game, const sf::Event &event) = 0;
    virtual void resize(sf::RenderWindow &window) = 0;
    virtual void update(Game *game) = 0;
    virtual void draw(sf::RenderTarget &renderTarget) = 0;

    bool isActive(){ return this->_isActive; }
    bool isPaused(){ return this->_isPaused; }

protected:
    bool _isActive;
    bool _isPaused;
};

#endif // GAMESTATE_H

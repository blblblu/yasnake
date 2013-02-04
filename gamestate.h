#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameengine.h"

class GameEngine;

class GameState
{
public:
    GameState(){}
    virtual ~GameState(){}

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvent(GameEngine *game, sf::Event *event) = 0;
    virtual void resize(GameEngine *game) = 0;
    virtual void update(GameEngine *game) = 0;
    virtual void draw(GameEngine *game, sf::RenderTarget *renderTarget) = 0;

    bool isActive(){ return this->_isActive; }
    bool isPaused(){ return this->_isPaused; }

protected:
    bool _isActive;
    bool _isPaused;
};

#endif // GAMESTATE_H

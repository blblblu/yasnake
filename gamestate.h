#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameengine.h"

using namespace std;

class GameEngine;

class GameState
{
public:
    GameState(){};
    ~GameState(){};

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvent(GameEngine *game, sf::Event *event) = 0;
    virtual void update(GameEngine *game) = 0;
    virtual void draw(GameEngine *game) = 0;

private:
    GameEngine* _game;
};

#endif // GAMESTATE_H

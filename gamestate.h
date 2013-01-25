#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameengine.h"

using namespace std;

class GameEngine;

class GameState
{
public:
    GameState();
    virtual ~GameState() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(GameEngine* game) = 0;
    virtual void update(GameEngine* game) = 0;
    virtual void draw(GameEngine* game) = 0;
};

#endif // GAMESTATE_H

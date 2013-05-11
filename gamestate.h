#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <deque>
#include <queue>
#include <string>

#include <SFML/Graphics.hpp>

#include "debugoutput.h"
#include "stateevent.h"

class GameState
{
public:
    GameState();
    virtual ~GameState(){}

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvent(const sf::Event &event) = 0;
    virtual sf::View resize(const unsigned int x, const unsigned int y) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget &renderTarget) = 0;

    bool isActive();
    bool isPaused();

    bool pollStateEvent(StateEvent &stateEvent);

protected:
    void addStateEvent(const StateEvent &stateEvent);

    bool m_isActive;
    bool m_isPaused;

private:
    std::queue<StateEvent> m_stateEvents;
};

#endif // GAMESTATE_H

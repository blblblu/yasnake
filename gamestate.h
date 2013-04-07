#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

#include <SFML/Graphics.hpp>

#include "debugoutput.h"
#include "statechangetype.h"

class GameState
{
public:
    GameState(sf::RenderTarget *renderTarget);
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

    bool stateChange(int &stateChangeType, std::string &nextState);

protected:
    void changeState(const unsigned int stateChangeType, const std::string &nextState = "");

    bool _isActive;
    bool _isPaused;

    sf::RenderTarget *_renderTarget;

private:
    unsigned int _stateChangeType;
    std::string _nextState;
};

#endif // GAMESTATE_H

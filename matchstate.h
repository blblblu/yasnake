#ifndef MATCHSTATE_H
#define MATCHSTATE_H

#include "gamestate.h"

class MatchState : public GameState
{
public:
    MatchState();
    ~MatchState();

    void start();
    void stop();

    void pause();
    void resume();

    void handleEvent(GameEngine *game, sf::Event *event);
    void resize(GameEngine *game);
    void update(GameEngine *game);
    void draw(GameEngine *game, sf::RenderTarget *renderTarget);
};

#endif // MATCHSTATE_H

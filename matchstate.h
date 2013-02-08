#ifndef MATCHSTATE_H
#define MATCHSTATE_H

#include <memory>

#include "game.h"
#include "gamestate.h"

class MatchState : public GameState
{
public:
    MatchState();
    ~MatchState();

    void start(sf::RenderWindow &window);
    void stop();

    void pause(sf::RenderWindow &window);
    void resume(sf::RenderWindow &window);

    void handleEvent(Game *game, const sf::Event &event);
    void resize(sf::RenderWindow &window);
    void update(Game *game);
    void draw(sf::RenderTarget &renderTarget);

private:
    std::unique_ptr<sf::RectangleShape> _field;
};

#endif // MATCHSTATE_H

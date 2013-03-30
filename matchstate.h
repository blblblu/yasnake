#ifndef MATCHSTATE_H
#define MATCHSTATE_H

#include <iostream>
#include <memory>

#include <SFML/System.hpp>

#include "gamestate.h"
#include "inttostring.h"

class MatchState : public GameState
{
public:
    MatchState(sf::RenderTarget *renderTarget);
    ~MatchState();

    void start();
    void stop();

    void pause();
    void resume();

    void handleEvent(const sf::Event &event);
    sf::View resize(const unsigned int x, const unsigned int y);
    void update();
    void draw(sf::RenderTarget &renderTarget);

private:
    std::unique_ptr<sf::Font> _sourceSansPro;

    std::unique_ptr<sf::Clock> _clock;
    std::unique_ptr<sf::Time> _additionalTime;

    std::unique_ptr<sf::RectangleShape> _field;
    std::vector<sf::RectangleShape> _fieldPoints;
    std::unique_ptr<sf::Text> _time;
    std::unique_ptr<sf::RectangleShape> _square;
};

#endif // MATCHSTATE_H

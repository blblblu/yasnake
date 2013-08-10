#ifndef MATCHSTATE_H
#define MATCHSTATE_H

#include <iostream>
#include <memory>

#include <boost/lexical_cast.hpp>
#include <SFML/System.hpp>

#include "gamestate.hpp"
#include "player.hpp"

class MatchState : public GameState
{
public:
    MatchState();
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
    std::unique_ptr<sf::Font> m_sourceSansPro;

    std::unique_ptr<sf::Clock> m_clock;
    std::unique_ptr<sf::Time> m_additionalTime;

    std::unique_ptr<sf::RectangleShape> m_field;
    std::vector<sf::RectangleShape> m_fieldPoints;
    std::unique_ptr<sf::Text> m_time;
    std::unique_ptr<sf::RectangleShape> m_square;

    std::unique_ptr<Player> m_player;
};

#endif // MATCHSTATE_H

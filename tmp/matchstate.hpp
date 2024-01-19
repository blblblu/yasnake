#ifndef MATCHSTATE_H
#define MATCHSTATE_H

#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>

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
    void randomizeTargetPosition();

    double m_score;

    std::unique_ptr<sf::Font> m_sourceSansPro;

    std::unique_ptr<sf::Clock> m_clock;
    std::unique_ptr<sf::Time> m_overallTime;

    std::unique_ptr<sf::RectangleShape> m_field;
    std::vector<sf::RectangleShape> m_fieldPoints;

    std::unique_ptr<sf::Text> m_keyboardCommands;
    std::unique_ptr<sf::Text> m_scoreText;
    std::unique_ptr<sf::Text> m_timeText;

    std::unique_ptr<Player> m_player;
    std::unique_ptr<sf::RectangleShape> m_target;

    std::uniform_int_distribution<> m_distributionX; // Zahlenverteilung betreffend x-Achse
    std::uniform_int_distribution<> m_distributionY; // Zahlenverteilung betreffend x-Achse
    std::mt19937 m_engine; // Mersenne-Twister
};

#endif // MATCHSTATE_H

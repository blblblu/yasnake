#pragma once

#include <states/gamestate.h>

#include <memory>

class ScoreState : public GameState
{
public:
    ScoreState();
    ~ScoreState();

    void start();
    void stop();

    void pause();
    void resume();

    void handleEvent(const sf::Event &event);
    sf::View resize(const unsigned int x, const unsigned int y);
    void update();
    void draw(sf::RenderTarget &renderTarget);

    void updateScore(const unsigned int highscore, const unsigned int score);

private:
    std::unique_ptr<sf::Font> m_sourceSansPro;
    std::unique_ptr<sf::Text> m_heading;
    std::unique_ptr<sf::Text> m_highscoreText;
    std::unique_ptr<sf::Text> m_keyboardCommands;
    std::unique_ptr<sf::Text> m_scoreText;

    unsigned int m_highscore;
    unsigned int m_score;
};

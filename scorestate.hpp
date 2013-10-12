#ifndef SCORESTATE_H
#define SCORESTATE_H

#include <memory>

#include "gamestate.hpp"

class ScoreState : public ScoreState
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

private:
    std::unique_ptr<sf::Font> m_sourceSansPro;
    std::unique_ptr<sf::Text> m_heading;
    std::unique_ptr<sf::Text> m_highscore;
    std::unique_ptr<sf::Text> m_score;
};

#endif // SCORESTATE_H

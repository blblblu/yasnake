#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <memory>

#include "gamestate.hpp"

class PauseState : public GameState
{
public:
    PauseState();
    ~PauseState();

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
    std::unique_ptr<sf::Text> m_text;
};

#endif // PAUSESTATE_H

#pragma once

#include <iostream>
#include <memory>

#include "gamestate.h"

class MenuState : public GameState
{
public:
    MenuState();
    ~MenuState();

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
    std::unique_ptr<sf::Text> m_title;
    std::unique_ptr<sf::Text> m_name;
    std::unique_ptr<sf::Text> m_keyboardCommands;
};

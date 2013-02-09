#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <iostream>
#include <memory>

#include "gamestate.h"

class IntroState : public GameState
{
public:
    IntroState(sf::RenderTarget *renderTarget);
    ~IntroState();

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
    std::unique_ptr<sf::Text> _title;
    std::unique_ptr<sf::Text> _name;
    std::unique_ptr<sf::Text> _keyboardCommands;

    std::unique_ptr<sf::Text> _debug;
};

#endif // INTROSTATE_H

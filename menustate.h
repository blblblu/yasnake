#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <iostream>
#include <memory>

#include "gamestate.h"

class MenuState : public GameState
{
public:
    MenuState(sf::RenderTarget *renderTarget);
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
    std::unique_ptr<sf::Font> _sourceSansPro;
    std::unique_ptr<sf::Text> _title;
    std::unique_ptr<sf::Text> _name;
    std::unique_ptr<sf::Text> _keyboardCommands;

    std::unique_ptr<sf::Text> _debug;
};

#endif // MENUSTATE_H

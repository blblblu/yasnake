#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdexcept>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "debugoutput.h"
#include "menustate.h"
#include "matchstate.h"
#include "stateevent.h"
#include "statemanager.h"

class StateManager;

class Game
{
public:
    Game(sf::VideoMode videoMode, const std::string &title);
    ~Game();

    void create(sf::VideoMode videoMode, const std::string &title);
    void close();

    void loop();

    bool isOpen();

private:
    void handleStateEvents();
    void handleEvents();
    void update();
    void draw();

    StateManager m_stateManager;
    sf::RenderWindow m_window;
};

#endif // GAME_H

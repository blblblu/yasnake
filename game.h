#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdexcept>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "introstate.h"
#include "matchstate.h"
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

    void handleStateChange();
    void handleEvents();
    void update();
    void draw();

    bool isOpen();

    sf::RenderWindow window;

    sf::Music music;

private:
    StateManager _stateManager;
};

#endif // GAME_H

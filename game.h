#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "statemanager.h"

class StateManager;

class Game
{
public:
    Game(sf::VideoMode videoMode, const std::string &title);
    ~Game();

    void create(sf::VideoMode videoMode, const std::string &title);

    void handleEvents();
    void update();
    void draw();

    bool isOpen();
    void close();

    sf::RenderWindow window;
    StateManager stateManager;
};

#endif // GAME_H

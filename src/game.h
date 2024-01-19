#pragma once

#include <statemanager.h>

#include <SFML/Window.hpp>

class StateManager;

class Game
{
public:
    Game();
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

    void submitScore(const unsigned int score);

    StateManager m_stateManager;
    sf::RenderWindow m_window;

    unsigned int m_highscore;
    unsigned int m_lastScore;
};

#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "debugoutput.hpp"
#include "menustate.hpp"
#include "matchstate.hpp"
#include "pausestate.hpp"
#include "scorestate.hpp"
#include "stateevent.hpp"
#include "statemanager.hpp"

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

#endif // GAME_H

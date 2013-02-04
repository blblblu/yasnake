#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <memory>

#include "gamestate.h"

class IntroState : public GameState
{
public:
    IntroState();
    ~IntroState();

    void start();
    void stop();

    void pause();
    void resume();

    void handleEvent(GameEngine *game, sf::Event *event);
    void resize(GameEngine *game);
    void update(GameEngine *game);
    void draw(GameEngine *game, sf::RenderTarget *renderTarget);

private:
    std::unique_ptr<sf::Font> _sourceSansPro;
    std::unique_ptr<sf::Text> _title;
    std::unique_ptr<sf::Text> _name;
    std::unique_ptr<sf::Text> _keyboardCommands;

    std::unique_ptr<sf::Text> _debug;
};

#endif // INTROSTATE_H

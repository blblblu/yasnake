#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <memory>

#include "game.h"
#include "gamestate.h"

class IntroState : public GameState
{
public:
    IntroState();
    ~IntroState();

    void start(sf::RenderWindow &window);
    void stop();

    void pause(sf::RenderWindow &window);
    void resume(sf::RenderWindow &window);

    void handleEvent(Game *game, const sf::Event &event);
    void resize(sf::RenderWindow &window);
    void update(Game *game);
    void draw(sf::RenderTarget &renderTarget);

private:
    std::unique_ptr<sf::Font> _sourceSansPro;
    std::unique_ptr<sf::Text> _title;
    std::unique_ptr<sf::Text> _name;
    std::unique_ptr<sf::Text> _keyboardCommands;

    std::unique_ptr<sf::Text> _debug;
};

#endif // INTROSTATE_H

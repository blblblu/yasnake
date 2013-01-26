#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "gamestate.h"

using namespace std;

class IntroState : public GameState
{
public:
    IntroState();
    ~IntroState();

    void pause();
    void resume();

    void handleEvent(GameEngine *game, sf::Event *event);
    void update(GameEngine *game);
    void draw(GameEngine *game);

private:
    sf::Font _sourceSansPro;
    sf::Text _title;
    sf::Text _name;
    sf::Text _keyboardCommands;

//    shared_ptr<sf::Texture> _texture;
//    shared_ptr<sf::Sprite> _sprite;
};

#endif // INTROSTATE_H

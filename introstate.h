#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <memory>

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
    GameEngine* _game;

    shared_ptr<sf::Texture> _texture;
    shared_ptr<sf::Sprite> _sprite;
};

#endif // INTROSTATE_H

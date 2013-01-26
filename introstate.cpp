#include "introstate.h"

IntroState::IntroState()
{
//    // TODO Fehlerabfrage
//    this->_texture = shared_ptr<sf::Texture>(new sf::Texture());
//    this->_texture->loadFromFile("intro.png");
//
//    this->_sprite = shared_ptr<sf::Sprite>(new sf::Sprite(*this->_texture));
    this->_sourceSansPro.loadFromFile("SourceSansPro-Light.ttf");
    this->_title.setString("TowerDefense");
    this->_title.setFont(this->_sourceSansPro);
    this->_title.setCharacterSize(40);
    this->_title.setColor(sf::Color(133, 153, 0));
    this->_title.setPosition(sf::Vector2f(30, 30));

    this->_name.setString("Sebastian Schulz");
    this->_name.setFont(this->_sourceSansPro);
    this->_name.setCharacterSize(20);
    this->_name.setColor(sf::Color(42, 161, 152));
    this->_name.setPosition(sf::Vector2f(30, 75));

    this->_keyboardCommands.setString("N - New Game\nQ - Close");
    this->_keyboardCommands.setFont(this->_sourceSansPro);
    this->_keyboardCommands.setCharacterSize(20);
    this->_keyboardCommands.setColor(sf::Color(38, 139, 210));
    this->_keyboardCommands.setPosition(sf::Vector2f(30, 530));

    cout << "[IntroState] Initialization" << endl;
}

IntroState::~IntroState()
{
    cout << "[IntroState] Cleanup" << endl;
}

void IntroState::pause()
{
    cout << "[IntroState] Pause" << endl;
}

void IntroState::resume()
{
    cout << "[IntroState] Resume" << endl;
}

void IntroState::handleEvent(GameEngine *game, sf::Event *event)
{
    switch(event->type)
    {
    case sf::Event::KeyPressed:
        if(event->key.code == sf::Keyboard::Q)
            game->quit();
        break;
    }
}

void IntroState::update(GameEngine *game)
{
}

void IntroState::draw(GameEngine *game)
{
    game->window->clear(sf::Color(253, 246, 227));
    game->window->draw(this->_title);
    game->window->draw(this->_name);
    game->window->draw(this->_keyboardCommands);
}

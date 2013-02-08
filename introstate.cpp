#include "introstate.h"
#include <sstream>

IntroState::IntroState()
{
    std::cout << "[IntroState] initialization" << std::endl;
}

IntroState::~IntroState()
{
    std::cout << "[IntroState] cleanup" << std::endl;
}

void IntroState::start(sf::RenderWindow &window)
{
    std::cout << "[IntroState] start" << std::endl;

    this->_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->_title = std::unique_ptr<sf::Text>(new sf::Text("TowerDefense", *this->_sourceSansPro, 40));
    this->_title->setColor(sf::Color(133, 153, 0));
    this->_title->setPosition(sf::Vector2f(30, 30));

    this->_name = std::unique_ptr<sf::Text>(new sf::Text("Sebastian Schulz", *this->_sourceSansPro, 20));
    this->_name->setColor(sf::Color(42, 161, 152));
    this->_name->setPosition(sf::Vector2f(30, 75));

    this->_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("n - new game\nq - quit game", *this->_sourceSansPro, 20));
    this->_keyboardCommands->setColor(sf::Color(38, 139, 210));
    this->_keyboardCommands->setPosition(sf::Vector2f(30, 530));

    this->_debug = std::unique_ptr<sf::Text>(new sf::Text("0/0", *this->_sourceSansPro, 20));
    this->_debug->setColor(sf::Color(0, 0, 0));
    this->_debug->setPosition(sf::Vector2f(0, 0));

    // View zurücksetzen
    this->resize(window);

    this->_isActive = true;
}

void IntroState::stop()
{
    std::cout << "[IntroState] stop" << std::endl;

    this->_title = nullptr;
    this->_name = nullptr;
    this->_keyboardCommands = nullptr;

    this->_isActive = false;
}

void IntroState::pause(sf::RenderWindow &window)
{
    std::cout << "[IntroState] pause" << std::endl;

    this->_isPaused = true;
}

void IntroState::resume(sf::RenderWindow &window)
{
    std::cout << "[IntroState] resume" << std::endl;

    // View zurücksetzen lassen
    this->resize(window);

    this->_isPaused = false;
}

void IntroState::handleEvent(Game *game, const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Q)
            game->close();
        if(event.key.code == sf::Keyboard::N)
            game->stateManager.pushState("MatchState", game->window);
        break;
    }
}

void IntroState::resize(sf::RenderWindow &window)
{
    window.setView(sf::View(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize().x, window.getSize().y)));

    std::ostringstream tmp;
    tmp << window.getSize().x << "/" << window.getSize().y;
    this->_debug->setString(tmp.str());

    this->_keyboardCommands->setPosition(30, window.getSize().y - 90);
}

void IntroState::update(Game *game)
{
}

void IntroState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->_title);
    renderTarget.draw(*this->_name);
    renderTarget.draw(*this->_keyboardCommands);

    renderTarget.draw(*this->_debug);
}

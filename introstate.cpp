#include "introstate.h"
#include <sstream>

IntroState::IntroState(sf::RenderTarget *renderTarget) : GameState(renderTarget)
{
    DebugOutput::gameState("IntroState", "");
}

IntroState::~IntroState()
{
    DebugOutput::gameState("IntroState", "cleanup");
}

void IntroState::start()
{
    DebugOutput::gameState("IntroState", "start");

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

    this->_isActive = true;
}

void IntroState::stop()
{
    DebugOutput::gameState("IntroState", "stop");

    this->_title.reset();
    this->_name.reset();
    this->_keyboardCommands.reset();

    this->_isActive = false;
}

void IntroState::pause()
{
    DebugOutput::gameState("IntroState", "pause");

    this->_isPaused = true;
}

void IntroState::resume()
{
    DebugOutput::gameState("IntroState", "resume");

    this->_isPaused = false;
}

void IntroState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Q)
            this->changeState(StateChangeType::PopState);
        if(event.key.code == sf::Keyboard::N)
            this->changeState(StateChangeType::PushState, "MatchState");
        break;
    }
}

sf::View IntroState::resize(const unsigned int x, const unsigned int y)
{
    std::ostringstream tmp;
    tmp << x << "/" << y;
    this->_debug->setString(tmp.str());

    this->_keyboardCommands->setPosition(30, y - 90);

    return sf::View(sf::Vector2f(x / 2, y / 2), sf::Vector2f(x, y));
}

void IntroState::update()
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

#include "menustate.hpp"
#include <sstream>

MenuState::MenuState() : GameState()
{
    DebugOutput::gameState("MenuState", "initialization");
}

MenuState::~MenuState()
{
    DebugOutput::gameState("MenuState", "cleanup");
}

void MenuState::start()
{
    DebugOutput::gameState("MenuState", "start");

    this->m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->m_title = std::unique_ptr<sf::Text>(new sf::Text("Yet Another Snake Clone", *this->m_sourceSansPro, 40));
    this->m_title->setColor(sf::Color(133, 153, 0));
    this->m_title->setPosition(sf::Vector2f(30, 30));

    this->m_name = std::unique_ptr<sf::Text>(new sf::Text("Sebastian Schulz", *this->m_sourceSansPro, 20));
    this->m_name->setColor(sf::Color(42, 161, 152));
    this->m_name->setPosition(sf::Vector2f(30, 75));

    this->m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("n - new game\nq - quit game", *this->m_sourceSansPro, 20));
    this->m_keyboardCommands->setColor(sf::Color(38, 139, 210));
    this->m_keyboardCommands->setPosition(sf::Vector2f(30, 530));

    this->m_debug = std::unique_ptr<sf::Text>(new sf::Text("0/0", *this->m_sourceSansPro, 20));
    this->m_debug->setColor(sf::Color(0, 0, 0));
    this->m_debug->setPosition(sf::Vector2f(0, 0));

    this->m_isActive = true;
}

void MenuState::stop()
{
    DebugOutput::gameState("MenuState", "stop");

    this->m_title.release();
    this->m_name.release();
    this->m_keyboardCommands.release();

    this->m_isActive = false;
}

void MenuState::pause()
{
    DebugOutput::gameState("MenuState", "pause");

    this->m_isPaused = true;
}

void MenuState::resume()
{
    DebugOutput::gameState("MenuState", "resume");

    this->m_isPaused = false;
}

void MenuState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Q)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::PopState;
            this->addStateEvent(stateEvent);
        }
        if(event.key.code == sf::Keyboard::N)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::PushState;
            stateEvent.data = StateEvent::StateChangeEvent("MatchState");
            this->addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View MenuState::resize(const unsigned int x, const unsigned int y)
{
    std::ostringstream tmp;
    tmp << x << "/" << y;
    this->m_debug->setString(tmp.str());

    this->m_keyboardCommands->setPosition(30, y - 90);

    return sf::View(sf::Vector2f(x / 2, y / 2), sf::Vector2f(x, y));
}

void MenuState::update()
{
}

void MenuState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_title);
    renderTarget.draw(*this->m_name);
    renderTarget.draw(*this->m_keyboardCommands);

    renderTarget.draw(*this->m_debug);
}

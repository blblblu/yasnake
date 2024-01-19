#include "menustate.h"

#include <debugoutput.h>

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

    m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    m_title = std::unique_ptr<sf::Text>(new sf::Text("Snake", *m_sourceSansPro, 60));
    m_title->setFillColor(sf::Color(133, 153, 0));
    m_title->setPosition(sf::Vector2f(30, 10));

    m_name = std::unique_ptr<sf::Text>(new sf::Text("Sebastian Schulz", *m_sourceSansPro, 20));
    m_name->setFillColor(sf::Color(42, 161, 152));
    m_name->setPosition(sf::Vector2f(30, 75));

    m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[Enter] - neues Spiel\n[Escape] - Spiel beenden", *m_sourceSansPro, 20));
    m_keyboardCommands->setFillColor(sf::Color(38, 139, 210));
    m_keyboardCommands->setPosition(sf::Vector2f(30, 530));
}

void MenuState::stop()
{
    DebugOutput::gameState("MenuState", "stop");

    m_sourceSansPro.release();
    m_title.release();
    m_name.release();
    m_keyboardCommands.release();
}

void MenuState::pause()
{
    DebugOutput::gameState("MenuState", "pause");
}

void MenuState::resume()
{
    DebugOutput::gameState("MenuState", "resume");
}

void MenuState::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::EventType::PopState;
            addStateEvent(stateEvent);
        }
        if (event.key.code == sf::Keyboard::Return)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::EventType::PushState;
            stateEvent.data = StateEvent::StateChangeEvent("MatchState");
            addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View MenuState::resize(const unsigned int x, const unsigned int y)
{
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y - 30 - m_keyboardCommands->getLocalBounds().height));

    return sf::View(sf::Vector2f(x / 2.f, y / 2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void MenuState::update()
{
}

void MenuState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*m_title);
    renderTarget.draw(*m_name);
    renderTarget.draw(*m_keyboardCommands);
}

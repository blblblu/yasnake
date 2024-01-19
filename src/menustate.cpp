#include "menustate.h"

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

    this->m_title = std::unique_ptr<sf::Text>(new sf::Text("Snake", *this->m_sourceSansPro, 60));
    this->m_title->setFillColor(sf::Color(133, 153, 0));
    this->m_title->setPosition(sf::Vector2f(30, 10));

    this->m_name = std::unique_ptr<sf::Text>(new sf::Text("Sebastian Schulz", *this->m_sourceSansPro, 20));
    this->m_name->setFillColor(sf::Color(42, 161, 152));
    this->m_name->setPosition(sf::Vector2f(30, 75));

    this->m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[Enter] - neues Spiel\n[Escape] - Spiel beenden", *this->m_sourceSansPro, 20));
    this->m_keyboardCommands->setFillColor(sf::Color(38, 139, 210));
    this->m_keyboardCommands->setPosition(sf::Vector2f(30, 530));
}

void MenuState::stop()
{
    DebugOutput::gameState("MenuState", "stop");

    this->m_sourceSansPro.release();
    this->m_title.release();
    this->m_name.release();
    this->m_keyboardCommands.release();
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
            this->addStateEvent(stateEvent);
        }
        if (event.key.code == sf::Keyboard::Return)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::EventType::PushState;
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
    this->m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y - 30 - this->m_keyboardCommands->getLocalBounds().height));

    return sf::View(sf::Vector2f(x / 2.f, y / 2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
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
}

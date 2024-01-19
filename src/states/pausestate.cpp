#include "pausestate.h"

#include <debugoutput.h>

#include <sstream>

PauseState::PauseState() : GameState()
{
    DebugOutput::gameState("PauseState", "initialization");
}

PauseState::~PauseState()
{
    DebugOutput::gameState("PauseState", "cleanup");
}

void PauseState::start()
{
    DebugOutput::gameState("PauseState", "start");

    m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[space] continue game", *m_sourceSansPro, 20));
    m_keyboardCommands->setFillColor(sf::Color(38, 139, 210));
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(720-90));

    m_text = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *m_sourceSansPro, 80));
    m_text->setFillColor(sf::Color(133, 153, 0));
    m_text->setPosition(static_cast<float>(static_cast<int>((1280-m_text->getLocalBounds().width)/2.f)), static_cast<float>(static_cast<int>((720-m_text->getLocalBounds().height)/2.f)));
}

void PauseState::stop()
{
    DebugOutput::gameState("PauseState", "stop");

    m_keyboardCommands.release();
    m_sourceSansPro.release();
    m_text.release();
}

void PauseState::pause()
{
    DebugOutput::gameState("PauseState", "pause");
}

void PauseState::resume()
{
    DebugOutput::gameState("PauseState", "resume");
}

void PauseState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Space)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::EventType::PopState;
            addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View PauseState::resize(const unsigned int x, const unsigned int y)
{
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y-30-m_keyboardCommands->getLocalBounds().height));
    m_text->setPosition(static_cast<float>(static_cast<int>((x-m_text->getLocalBounds().width)/2.f)), static_cast<float>(static_cast<int>((y-m_text->getLocalBounds().height)/2.f)));

    return sf::View(sf::Vector2f(x/2.f, y/2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void PauseState::update()
{
}

void PauseState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*m_keyboardCommands);
    renderTarget.draw(*m_text);
}

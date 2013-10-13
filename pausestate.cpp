#include "pausestate.hpp"
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

    this->m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->m_text = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *this->m_sourceSansPro, 80));
    this->m_text->setColor(sf::Color(133, 153, 0));
    // doppeltes Umwandeln, um Unschärfe zu vermeiden
    this->m_text->setPosition(sf::Vector2f(static_cast<float>(static_cast<int>((1280-this->m_text->getLocalBounds().width)/2.f)), static_cast<float>(static_cast<int>((720-this->m_text->getLocalBounds().height)/2.f))));

    this->m_isActive = true;
}

void PauseState::stop()
{
    DebugOutput::gameState("PauseState", "stop");

    this->m_sourceSansPro.release();
    this->m_text.release();

    this->m_isActive = false;
}

void PauseState::pause()
{
    DebugOutput::gameState("PauseState", "pause");

    this->m_isPaused = true;
}

void PauseState::resume()
{
    DebugOutput::gameState("PauseState", "resume");

    this->m_isPaused = false;
}

void PauseState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::P)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::EventType::PopState;
            this->addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View PauseState::resize(const unsigned int x, const unsigned int y)
{
    if((static_cast<float>(x) / static_cast<float>(y)) <= (16.f / 9.f))
    {
        float z = (640.f * y) / x - 360.f;
        return sf::View(sf::Vector2f(640, 360), sf::Vector2f(1280, (720 + (2 * z))));
    }
    else
    {
        float z = (360.f * x) / y - 640.f;
        return sf::View(sf::Vector2f(640, 360), sf::Vector2f((1280 + (2 * z)), 720));
    }
}

void PauseState::update()
{
}

void PauseState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_text);
}

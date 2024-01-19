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

    this->m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[Leer] Spiel fortsetzen", *this->m_sourceSansPro, 20));
    this->m_keyboardCommands->setColor(sf::Color(38, 139, 210));
    this->m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(720-90));

    this->m_text = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *this->m_sourceSansPro, 80));
    this->m_text->setColor(sf::Color(133, 153, 0));
    // doppeltes Umwandeln, um Unschärfe zu vermeiden
    this->m_text->setPosition(static_cast<float>(static_cast<int>((1280-this->m_text->getLocalBounds().width)/2.f)), static_cast<float>(static_cast<int>((720-this->m_text->getLocalBounds().height)/2.f)));
}

void PauseState::stop()
{
    DebugOutput::gameState("PauseState", "stop");

    this->m_keyboardCommands.release();
    this->m_sourceSansPro.release();
    this->m_text.release();
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
            this->addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View PauseState::resize(const unsigned int x, const unsigned int y)
{
    this->m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y-30-this->m_keyboardCommands->getLocalBounds().height));
    this->m_text->setPosition(static_cast<float>(static_cast<int>((x-this->m_text->getLocalBounds().width)/2.f)), static_cast<float>(static_cast<int>((y-this->m_text->getLocalBounds().height)/2.f)));

    return sf::View(sf::Vector2f(x/2.f, y/2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void PauseState::update()
{
}

void PauseState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_keyboardCommands);
    renderTarget.draw(*this->m_text);
}

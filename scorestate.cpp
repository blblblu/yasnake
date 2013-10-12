#include "scorestate.hpp"
#include <sstream>

ScoreState::ScoreState() : GameState()
{
    DebugOutput::gameState("ScoreState", "initialization");
}

ScoreState::~ScoreState()
{
    DebugOutput::gameState("ScoreState", "cleanup");
}

void ScoreState::start()
{
    DebugOutput::gameState("ScoreState", "start");

    this->m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->m_heading = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *this->m_sourceSansPro, 60));
    this->m_heading->setColor(sf::Color(133, 153, 0));
    this->m_heading->setPosition(sf::Vector2f((1280-this->m_heading->getLocalBounds().width)/2.f, (720-this->m_heading->getLocalBounds().height)/2.f));

    this->m_highscore = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *this->m_sourceSansPro, 60));
    this->m_highscore->setColor(sf::Color(133, 153, 0));
    this->m_highscore->setPosition(sf::Vector2f((1280-this->m_heading->getLocalBounds().width)/2.f, (720-this->m_heading->getLocalBounds().height)/2.f));

    this->m_score = std::unique_ptr<sf::Text>(new sf::Text("PAUSE", *this->m_sourceSansPro, 60));
    this->m_score->setColor(sf::Color(133, 153, 0));
    this->m_score->setPosition(sf::Vector2f((1280-this->m_heading->getLocalBounds().width)/2.f, (720-this->m_heading->getLocalBounds().height)/2.f));

    this->m_isActive = true;
}

void ScoreState::stop()
{
    DebugOutput::gameState("ScoreState", "stop");

    this->m_heading.release();
    this->m_highscore.release();
    this->m_score.release();

    this->m_isActive = false;
}

void ScoreState::pause()
{
    DebugOutput::gameState("ScoreState", "pause");

    this->m_isPaused = true;
}

void ScoreState::resume()
{
    DebugOutput::gameState("ScoreState", "resume");

    this->m_isPaused = false;
}

void ScoreState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::P)
        {
            StateEvent stateEvent;
            stateEvent.type = StateEvent::PopState;
            this->addStateEvent(stateEvent);
        }
        break;
    default:
        break;
    }
}

sf::View ScoreState::resize(const unsigned int x, const unsigned int y)
{
    return sf::View(sf::FloatRect(0, 0, 1280, 720));
}

void ScoreState::update()
{
}

void ScoreState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_heading);
    renderTarget.draw(*this->m_highscore);
    renderTarget.draw(*this->m_score);
}

#include "scorestate.h"

#include <debugoutput.h>

#include <sstream>

ScoreState::ScoreState() : GameState(), m_highscore{0}, m_score{0}
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

    m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    m_heading = std::unique_ptr<sf::Text>(new sf::Text("Game Over", *m_sourceSansPro, 60));
    m_heading->setFillColor(sf::Color(220, 50, 47));
    m_heading->setPosition(sf::Vector2f(30, 10));

    m_highscoreText = std::unique_ptr<sf::Text>(new sf::Text("Highscore: " + std::to_string(m_highscore), *m_sourceSansPro, 40));
    m_highscoreText->setFillColor(sf::Color(133, 153, 0));
    m_highscoreText->setPosition(sf::Vector2f(30, 140));

    m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[Enter] fortfahren", *m_sourceSansPro, 20));
    m_keyboardCommands->setFillColor(sf::Color(38, 139, 210));
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(720 - 90));

    m_scoreText = std::unique_ptr<sf::Text>(new sf::Text("Punktzahl: " + std::to_string(m_score), *m_sourceSansPro, 40));
    m_scoreText->setFillColor(sf::Color(181, 137, 0));
    m_scoreText->setPosition(sf::Vector2f(30, 95));
}

void ScoreState::stop()
{
    DebugOutput::gameState("ScoreState", "stop");

    m_sourceSansPro.release();
    m_heading.release();
    m_highscoreText.release();
    m_keyboardCommands.release();
    m_scoreText.release();
}

void ScoreState::pause()
{
    DebugOutput::gameState("ScoreState", "pause");
}

void ScoreState::resume()
{
    DebugOutput::gameState("ScoreState", "resume");
}

void ScoreState::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Return)
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

sf::View ScoreState::resize(const unsigned int x, const unsigned int y)
{
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y - 30 - m_keyboardCommands->getLocalBounds().height));

    return sf::View(sf::Vector2f(x / 2.f, y / 2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void ScoreState::update()
{
}

void ScoreState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*m_heading);
    renderTarget.draw(*m_highscoreText);
    renderTarget.draw(*m_keyboardCommands);
    renderTarget.draw(*m_scoreText);
}

void ScoreState::updateScore(const unsigned int highscore, const unsigned int score)
{
    m_highscore = highscore;
    m_score = score;

    if (isActive())
    {
        m_highscoreText->setString("Highscore: " + std::to_string(m_highscore));
        m_scoreText->setString("Punktzahl: " + std::to_string(m_score));
    }
}

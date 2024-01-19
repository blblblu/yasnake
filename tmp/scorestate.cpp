#include "scorestate.hpp"
#include <sstream>

ScoreState::ScoreState() : GameState()
{
    DebugOutput::gameState("ScoreState", "initialization");

    // Punktzahlen auf 0 setzen
    this->m_highscore = 0;
    this->m_score = 0;
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

    this->m_heading = std::unique_ptr<sf::Text>(new sf::Text("Game Over", *this->m_sourceSansPro, 60));
    this->m_heading->setColor(sf::Color(220, 50, 47));
    this->m_heading->setPosition(sf::Vector2f(30, 10));

    this->m_highscoreText = std::unique_ptr<sf::Text>(new sf::Text("Highscore: "+boost::lexical_cast<std::string>(this->m_highscore), *this->m_sourceSansPro, 40));
    this->m_highscoreText->setColor(sf::Color(133, 153, 0));
    this->m_highscoreText->setPosition(sf::Vector2f(30, 140));

    this->m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[Enter] fortfahren", *this->m_sourceSansPro, 20));
    this->m_keyboardCommands->setColor(sf::Color(38, 139, 210));
    this->m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(720-90));

    this->m_scoreText = std::unique_ptr<sf::Text>(new sf::Text("Punktzahl: "+boost::lexical_cast<std::string>(this->m_score), *this->m_sourceSansPro, 40));
    this->m_scoreText->setColor(sf::Color(181, 137, 0));
    this->m_scoreText->setPosition(sf::Vector2f(30, 95));
}

void ScoreState::stop()
{
    DebugOutput::gameState("ScoreState", "stop");

    this->m_sourceSansPro.release();
    this->m_heading.release();
    this->m_highscoreText.release();
    this->m_keyboardCommands.release();
    this->m_scoreText.release();
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
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Return)
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

sf::View ScoreState::resize(const unsigned int x, const unsigned int y)
{
    this->m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(y-30-this->m_keyboardCommands->getLocalBounds().height));

    return sf::View(sf::Vector2f(x/2.f, y/2.f), sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void ScoreState::update()
{
}

void ScoreState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_heading);
    renderTarget.draw(*this->m_highscoreText);
    renderTarget.draw(*this->m_keyboardCommands);
    renderTarget.draw(*this->m_scoreText);
}

void ScoreState::updateScore(const unsigned int highscore, const unsigned int score)
{
    this->m_highscore = highscore;
    this->m_score = score;

    // wenn Gamestate aktiv ist, Text aktualisieren
    if(this->isActive())
    {
        this->m_highscoreText->setString("Highscore: "+boost::lexical_cast<std::string>(this->m_highscore));
        this->m_scoreText->setString("Punktzahl: "+boost::lexical_cast<std::string>(this->m_score));
    }
}

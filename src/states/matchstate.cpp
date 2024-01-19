#include "matchstate.h"

#include <debugoutput.h>

MatchState::MatchState() : GameState(), m_distributionX(std::uniform_int_distribution<>(0, 4 * 16 - 1)), m_distributionY(std::uniform_int_distribution<>(0, 4 * 9 - 1))
{
    DebugOutput::gameState("MatchState", "initialization");
}

MatchState::~MatchState()
{
    DebugOutput::gameState("MatchState", "cleanup");
}

void MatchState::start()
{
    DebugOutput::gameState("MatchState", "start");

    m_score = 0;

    m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    m_clock = std::unique_ptr<sf::Clock>(new sf::Clock());
    m_clock->restart();

    m_overallTime = std::unique_ptr<sf::Time>(new sf::Time());

    m_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f((64 * 16), (64 * 9))));
    m_field->setFillColor(sf::Color(238, 232, 213));

    for (int i = 1; i < 16; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(2, 2));
            r.setPosition(static_cast<float>((i * 64) - 1), static_cast<float>((j * 64) - 1));
            r.setFillColor(sf::Color(181, 137, 0));
            m_fieldPoints.push_back(r);
        }
    }

    m_keyboardCommands = std::unique_ptr<sf::Text>(new sf::Text("[space] pause game", *m_sourceSansPro, 20));
    m_keyboardCommands->setFillColor(sf::Color(38, 139, 210));
    m_keyboardCommands->setPosition(static_cast<float>(30), static_cast<float>(720 - 72 - 30 - m_keyboardCommands->getLocalBounds().height));

    m_scoreText = std::unique_ptr<sf::Text>(new sf::Text("", *m_sourceSansPro, 60));
    m_scoreText->setFillColor(sf::Color(133, 153, 0));
    m_scoreText->setPosition(sf::Vector2f(0, -72));

    m_timeText = std::unique_ptr<sf::Text>(new sf::Text("", *m_sourceSansPro, 60));
    m_timeText->setFillColor(sf::Color(42, 161, 152));

    m_player = std::unique_ptr<Player>(new Player(sf::Vector2f((64 * 8), (64 * 4.5)), Direction::Up));
    m_target = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(16, 16)));
    m_target->setFillColor(sf::Color(38, 139, 210));

    m_engine.seed(static_cast<unsigned long>(time(NULL)));

    randomizeTargetPosition();
}

void MatchState::stop()
{
    DebugOutput::gameState("MatchState", "stop");

    m_sourceSansPro.release();
    m_clock.release();
    m_overallTime.release();
    m_field.release();
    m_fieldPoints.clear();
    m_keyboardCommands.release();
    m_scoreText.release();
    m_timeText.release();
    m_player.release();
    m_target.release();
}

void MatchState::pause()
{
    DebugOutput::gameState("MatchState", "pause");
}

void MatchState::resume()
{
    DebugOutput::gameState("MatchState", "resume");

    m_clock->restart();
}

void MatchState::handleEvent(const sf::Event &event)
{
    StateEvent stateEvent;

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Q:
            stateEvent.type = StateEvent::EventType::PopState;
            addStateEvent(stateEvent);
            break;
        case sf::Keyboard::Space:
            stateEvent.type = StateEvent::EventType::PushState;
            stateEvent.data = StateEvent::StateChangeEvent("PauseState");
            addStateEvent(stateEvent);
            break;
        // Spielersteuerung
        case sf::Keyboard::Up:
            if (m_player->getDirection() != Direction::Up && m_player->getDirection() != Direction::Down)
                m_player->changeDirection(Direction::Up);
            break;
        case sf::Keyboard::Down:
            if (m_player->getDirection() != Direction::Up && m_player->getDirection() != Direction::Down)
                m_player->changeDirection(Direction::Down);
            break;
        case sf::Keyboard::Left:
            if (m_player->getDirection() != Direction::Left && m_player->getDirection() != Direction::Right)
                m_player->changeDirection(Direction::Left);
            break;
        case sf::Keyboard::Right:
            if (m_player->getDirection() != Direction::Left && m_player->getDirection() != Direction::Right)
                m_player->changeDirection(Direction::Right);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

sf::View MatchState::resize(const unsigned int x, const unsigned int y)
{
    // return sf::View(sf::Vector2f(350, 200), sf::Vector2f(x, y));

    // return sf::View(sf::Vector2f(350, 200), sf::Vector2f(800, 600));

    // TODO remove...

    //    unsigned int height = (1920 * y) / x;
    //    unsigned int displace = (height - 1080) / (-2);
    //    return sf::View(sf::FloatRect(0, displace, 1920, height));

    // (1920 / 2) = 960
    // (1080 / 2) = 540
    // 1280 × 720
    // / 2
    // 640 x 360
    //
    // 64 * 16 = 1024
    // 1024 / 2 = 512
    //
    // 64 * 9 = 576
    // 576 / 2 = 288
    if ((static_cast<float>(x) / static_cast<float>(y)) <= (16.f / 9.f))
    {
        float z = (640.f * y) / x - 360.f;
        return sf::View(sf::Vector2f(512, 288), sf::Vector2f(1280, (720 + (2 * z))));
    }
    else
    {
        float z = (360.f * x) / y - 640.f;
        return sf::View(sf::Vector2f(512, 288), sf::Vector2f((1280 + (2 * z)), 720));
    }
}

void MatchState::update()
{
    // _time->setString(intToString((_clock->getElapsedTime() + *_additionalTime).asSeconds()));

    // Berechnung der Bildfrequenz
    // doppelte Datentypumwandlung, um überflüssige Dezimalstellen zu vermeiden
    // m_HUDScore->setString(boost::lexical_cast<std::string>(static_cast<int>(1.f / m_clock->getElapsedTime().asSeconds())));

    // vergangene Zeit tempörär abspeichern, um fehlerhafte Berechnungen zu vermeiden, anschließend Uhr zurücksetzen
    sf::Time elapsedTime = m_clock->getElapsedTime();
    m_clock->restart();

    // Zeit und Punktzahl aktualisieren, wenn Spieler noch am Leben ist
    if (m_player->isAlive())
    {
        m_score += 0.0001 * elapsedTime.asSeconds() * std::pow(m_player->getMaximumLength(), 2);
        *m_overallTime += elapsedTime;
    }

    // Punkt- und Zeitanzeigen
    m_scoreText->setString(std::to_string(static_cast<int>(m_score)));
    // doppelte Datentypumwandlung, um überflüssige Dezimalstellen zu vermeiden
    m_timeText->setString(std::to_string(static_cast<int>(m_overallTime->asSeconds())));
    // Position von Zeitanzeige aktualisieren
    m_timeText->setPosition(sf::Vector2f(1024 - m_timeText->getLocalBounds().width, -72));

    // Spieler aktualisieren
    m_player->update(elapsedTime);
    // Spieler auf Kollision mit Hindernissen überprüfen
    if (m_player->firstElementIntersectsWithBoundaries())
        m_player->setLifeStatus(false);
    if (m_player->firstElementIntersectsWithPlayer())
        m_player->setLifeStatus(false);
    // Spieler auf Kollision mit Ziel-Quadrat überprüfen
    if (m_player->isAlive())
    {
        if (m_player->firstElementIntersectsWith(m_target->getGlobalBounds()))
        {
            m_player->setMaximumLength(1.25f * m_player->getMaximumLength());
            randomizeTargetPosition();
        }
    }
    // Gamestate beenden und Punktzahl dem Spiel übergeben, wenn Spieler beendet (inaktiv) ist
    if (!m_player->isActive())
    {
        // Punktzahl übergeben
        StateEvent scoreEvent;
        scoreEvent.type = StateEvent::EventType::SubmitScoreEvent;
        scoreEvent.data = StateEvent::SubmitScoreEvent(static_cast<int>(m_score));
        addStateEvent(scoreEvent);
        // Gamestate wechseln
        StateEvent stateChangeEvent;
        stateChangeEvent.type = StateEvent::EventType::ReplaceState;
        stateChangeEvent.data = StateEvent::StateChangeEvent("ScoreState");
        addStateEvent(stateChangeEvent);
    }
}

void MatchState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*m_field);
    for (sf::Drawable &d : m_fieldPoints)
    {
        renderTarget.draw(d);
    }
    renderTarget.draw(*m_keyboardCommands);
    renderTarget.draw(*m_scoreText);
    renderTarget.draw(*m_timeText);
    renderTarget.draw(*m_player);
    renderTarget.draw(*m_target);
}

void MatchState::randomizeTargetPosition()
{
    // Position des Ziel-Quadrates zufällig festlegen
    int newX = 16 * m_distributionX(m_engine);
    int newY = 16 * m_distributionY(m_engine);
    m_target->setPosition(sf::Vector2f(static_cast<float>(newX), static_cast<float>(newY)));
}

#include "game.h"

Game::Game()
{
    DebugOutput::game("initialization");
    create(sf::VideoMode(1280, 720), "Snake");

    // vorhandene Gamestates dem Statemanager bekanntmachen
    m_stateManager.addState("MatchState", new MatchState());
    m_stateManager.addState("MenuState", new MenuState());
    m_stateManager.addState("PauseState", new PauseState());
    m_stateManager.addState("ScoreState", new ScoreState());

    // Hauptmenü laden
    m_stateManager.pushState("MenuState");
    m_window.setView(m_stateManager.backActive()->resize(m_window.getSize().x, m_window.getSize().y));

    // Punktstände auf 0 setzen
    m_highscore = 0;
    m_lastScore = 0;

    // Highscore aus Datei laden, wenn diese vorhanden ist
    std::ifstream input;
    input.open("score.save", std::ios::binary | std::ios::in);
    if (input) // zum Abfangen von Fehlern, z.B. falls Spielstand noch nicht besteht
    {
        input >> m_highscore;
    }
    input.close();
}

Game::~Game()
{
    DebugOutput::game("cleanup");
}

void Game::create(sf::VideoMode videoMode, const std::string &title)
{
    DebugOutput::game("create");

    m_window.create(videoMode, title);
}

void Game::close()
{
    DebugOutput::game("close");
    m_window.close();
}

void Game::loop()
{
    // Fenster schließen, wenn kein GameState mehr aktiv ist
    if (m_stateManager.emptyActive())
        close();
    else
    {
        // TODO: Reihenfolge berichtigen
        handleEvents();
        update();
        draw();
        handleStateEvents();
    }
}

bool Game::isOpen()
{
    return m_window.isOpen();
}

void Game::handleStateEvents()
{
    StateEvent stateEvent;
    while (m_stateManager.backActive()->pollStateEvent(stateEvent))
    {
        switch (stateEvent.type)
        {
        case StateEvent::EventType::ReplaceState:
            m_stateManager.replaceState(std::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            m_window.setView(m_stateManager.backActive()->resize(m_window.getSize().x, m_window.getSize().y));
            break;
        case StateEvent::EventType::PushState:
            m_stateManager.pushState(std::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            m_window.setView(m_stateManager.backActive()->resize(m_window.getSize().x, m_window.getSize().y));
            break;
        case StateEvent::EventType::PopState:
            m_stateManager.popState();
            // View zurücksetzen
            if (!m_stateManager.emptyActive())
                m_window.setView(m_stateManager.backActive()->resize(m_window.getSize().x, m_window.getSize().y));
            break;
        case StateEvent::EventType::SubmitScoreEvent:
            submitScore(std::get<StateEvent::SubmitScoreEvent>(stateEvent.data).score);
            // neue Punktzahl dem ScoreState übergeben
            GameState *state;
            state = m_stateManager.getState("ScoreState");
            ScoreState *scoreState;
            scoreState = dynamic_cast<ScoreState *>(state);
            scoreState->updateScore(m_highscore, m_lastScore);
            break;
        default:
            break;
        }
        // Automatisch aufhören, sobald kein GameState mehr aktiv ist
        if (m_stateManager.emptyActive())
            break;
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
        if (event.type == sf::Event::Resized)
            m_window.setView(m_stateManager.backActive()->resize(event.size.width, event.size.height));

        m_stateManager.backActive()->handleEvent(event);
    }
}

void Game::update()
{
    m_stateManager.backActive()->update();
}

void Game::draw()
{
    m_window.clear(sf::Color(0, 0, 0));
    m_stateManager.backActive()->draw(m_window);
    m_window.display();
}

void Game::submitScore(const unsigned int score)
{
    m_lastScore = score;
    // Punktzahl speichern, wenn sie der neue Bestwert ist
    if (score > m_highscore)
    {
        m_highscore = score;
        std::ofstream output;
        output.open("score.save", std::ios::binary | std::ios::out | std::ios::trunc);
        if (!output)
        {
            throw std::runtime_error("Score file could not be opened");
        }
        else
        {
            output << m_highscore;
        }
        output.close();
    }
}

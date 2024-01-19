#include "game.h"

Game::Game()
{
    DebugOutput::game("initialization");
    this->create(sf::VideoMode(1280, 720), "Snake");

    // vorhandene Gamestates dem Statemanager bekanntmachen
    this->m_stateManager.addState("MatchState", new MatchState());
    this->m_stateManager.addState("MenuState", new MenuState());
    this->m_stateManager.addState("PauseState", new PauseState());
    this->m_stateManager.addState("ScoreState", new ScoreState());

    // Hauptmenü laden
    this->m_stateManager.pushState("MenuState");
    this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));

    // Punktstände auf 0 setzen
    this->m_highscore = 0;
    this->m_lastScore = 0;

    // Highscore aus Datei laden, wenn diese vorhanden ist
    std::ifstream input;
    input.open("score.save", std::ios::binary | std::ios::in);
    if (input) // zum Abfangen von Fehlern, z.B. falls Spielstand noch nicht besteht
    {
        input >> this->m_highscore;
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

    this->m_window.create(videoMode, title);
}

void Game::close()
{
    DebugOutput::game("close");
    this->m_window.close();
}

void Game::loop()
{
    // Fenster schließen, wenn kein GameState mehr aktiv ist
    if (this->m_stateManager.emptyActive())
        this->close();
    else
    {
        // TODO: Reihenfolge berichtigen
        this->handleEvents();
        this->update();
        this->draw();
        this->handleStateEvents();
    }
}

bool Game::isOpen()
{
    return this->m_window.isOpen();
}

void Game::handleStateEvents()
{
    StateEvent stateEvent;
    while (this->m_stateManager.backActive()->pollStateEvent(stateEvent))
    {
        switch (stateEvent.type)
        {
        case StateEvent::EventType::ReplaceState:
            this->m_stateManager.replaceState(std::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        case StateEvent::EventType::PushState:
            this->m_stateManager.pushState(std::get<StateEvent::StateChangeEvent>(stateEvent.data).name);
            // View zurücksetzen
            this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        case StateEvent::EventType::PopState:
            this->m_stateManager.popState();
            // View zurücksetzen
            if (!this->m_stateManager.emptyActive())
                this->m_window.setView(this->m_stateManager.backActive()->resize(this->m_window.getSize().x, this->m_window.getSize().y));
            break;
        case StateEvent::EventType::SubmitScoreEvent:
            this->submitScore(std::get<StateEvent::SubmitScoreEvent>(stateEvent.data).score);
            // neue Punktzahl dem ScoreState übergeben
            GameState *state;
            state = this->m_stateManager.getState("ScoreState");
            ScoreState *scoreState;
            scoreState = dynamic_cast<ScoreState *>(state);
            scoreState->updateScore(this->m_highscore, this->m_lastScore);
            break;
        default:
            break;
        }
        // Automatisch aufhören, sobald kein GameState mehr aktiv ist
        if (this->m_stateManager.emptyActive())
            break;
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (this->m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->m_window.close();
        if (event.type == sf::Event::Resized)
            this->m_window.setView(this->m_stateManager.backActive()->resize(event.size.width, event.size.height));

        this->m_stateManager.backActive()->handleEvent(event);
    }
}

void Game::update()
{
    this->m_stateManager.backActive()->update();
}

void Game::draw()
{
    this->m_window.clear(sf::Color(0, 0, 0));
    this->m_stateManager.backActive()->draw(this->m_window);
    this->m_window.display();
}

void Game::submitScore(const unsigned int score)
{
    this->m_lastScore = score;
    // Punktzahl speichern, wenn sie der neue Bestwert ist
    if (score > this->m_highscore)
    {
        this->m_highscore = score;
        std::ofstream output;
        output.open("score.save", std::ios::binary | std::ios::out | std::ios::trunc);
        if (!output)
        {
            throw std::runtime_error("Score file could not be opened");
        }
        else
        {
            output << this->m_highscore;
        }
        output.close();
    }
}

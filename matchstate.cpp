#include "matchstate.hpp"

MatchState::MatchState() : GameState()
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

    this->m_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->m_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->m_clock = std::unique_ptr<sf::Clock>(new sf::Clock());
    this->m_clock->restart();

    this->m_additionalTime = std::unique_ptr<sf::Time>(new sf::Time());

    //this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(700, 400)));
    // TODO
    this->m_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f((64*16), (64*9))));
    this->m_field->setFillColor(sf::Color(238, 232, 213));
    //this->_field->setOutlineColor(sf::Color(181, 137, 0));
    //this->_field->setOutlineThickness(2);

    // TODO vielleicht besser mit Konstanten lösen...
    for(int i = 1; i < 16; i++)
    {
        for(int j = 1; j < 9; j++)
        {
            sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(2, 2));
            r.setPosition((i * 64) - 1, (j * 64) - 1);
            r.setFillColor(sf::Color(181, 137, 0));
            this->m_fieldPoints.push_back(r);
        }
    }

    this->m_time = std::unique_ptr<sf::Text>(new sf::Text("", *this->m_sourceSansPro, 40));
    this->m_time->setColor(sf::Color(42, 161, 152));
    this->m_time->setPosition(sf::Vector2f(30, 30));

    this->m_player = std::unique_ptr<Player>(new Player(sf::Vector2f((64*8), (64*4.5)), Direction::Up));

    this->m_isActive = true;
}

void MatchState::stop()
{
    DebugOutput::gameState("MatchState", "stop");

    this->m_sourceSansPro.release();
    this->m_clock.release();
    this->m_additionalTime.release();
    this->m_field.release();
    this->m_fieldPoints.clear();
    this->m_time.release();
    this->m_player.release();

    this->m_isActive = false;
}

void MatchState::pause()
{
    DebugOutput::gameState("MatchState", "pause");

    *this->m_additionalTime += this->m_clock->getElapsedTime();

    this->m_isPaused = true;
}

void MatchState::resume()
{
    DebugOutput::gameState("MatchState", "resume");

    this->m_clock->restart();

    this->m_isPaused = false;
}

void MatchState::handleEvent(const sf::Event &event)
{
    StateEvent stateEvent;

    switch(event.type)
    {
    case sf::Event::KeyPressed:
        switch(event.key.code)
        {
        case sf::Keyboard::Q:
            stateEvent.type = StateEvent::PopState;
            this->addStateEvent(stateEvent);
            break;
        // Spielersteuerung
        case sf::Keyboard::Up:
            if(this->m_player->getDirection() != Direction::Up && this->m_player->getDirection() != Direction::Down)
                this->m_player->changeDirection(Direction::Up);
            break;
        case sf::Keyboard::Down:
            if(this->m_player->getDirection() != Direction::Up && this->m_player->getDirection() != Direction::Down)
                this->m_player->changeDirection(Direction::Down);
            break;
        case sf::Keyboard::Left:
            if(this->m_player->getDirection() != Direction::Left && this->m_player->getDirection() != Direction::Right)
                this->m_player->changeDirection(Direction::Left);
            break;
        case sf::Keyboard::Right:
            if(this->m_player->getDirection() != Direction::Left && this->m_player->getDirection() != Direction::Right)
                this->m_player->changeDirection(Direction::Right);
            break;
        }
        break;
    default:
        break;
    }
}

sf::View MatchState::resize(const unsigned int x, const unsigned int y)
{
    //return sf::View(sf::Vector2f(350, 200), sf::Vector2f(x, y));

    //return sf::View(sf::Vector2f(350, 200), sf::Vector2f(800, 600));

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
    if((static_cast<float>(x) / static_cast<float>(y)) <= (16.f / 9.f))
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
    //this->_time->setString(intToString((this->_clock->getElapsedTime() + *this->_additionalTime).asSeconds()));

    // Berechnung der Bildfrequenz
    // doppelte Datentypumwandlung, um überflüssige Dezimalstellen zu vermeiden
    this->m_time->setString(boost::lexical_cast<std::string>(static_cast<int>(1.f / this->m_clock->getElapsedTime().asSeconds())));
    this->m_player->update(this->m_clock->getElapsedTime());
    if(this->m_player->firstElementIntersectsWithBoundaries())
        this->m_player->setLifeStatus(false);
    if(this->m_player->firstElementIntersectsWithPlayer())
        this->m_player->setLifeStatus(false);
    // Gamestate beenden, wenn Spieler beendet (inaktiv) ist
    if(!this->m_player->isActive())
    {
        StateEvent stateEvent;
        stateEvent.type = StateEvent::PopState;
        this->addStateEvent(stateEvent);
    }

    this->m_clock->restart();
}

void MatchState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->m_field);
    for(sf::Drawable &d: this->m_fieldPoints)
    {
        renderTarget.draw(d);
    }
    renderTarget.draw(*this->m_time);
    renderTarget.draw(*this->m_player);
}

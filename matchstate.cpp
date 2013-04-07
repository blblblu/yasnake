#include "matchstate.h"

MatchState::MatchState(sf::RenderTarget *renderTarget) : GameState(renderTarget)
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

    this->_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->_clock = std::unique_ptr<sf::Clock>(new sf::Clock());
    this->_clock->restart();

    this->_additionalTime = std::unique_ptr<sf::Time>(new sf::Time());

    //this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(700, 400)));
    // TODO
    this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f((64*16), (64*9))));
    this->_field->setFillColor(sf::Color(238, 232, 213));
    //this->_field->setOutlineColor(sf::Color(181, 137, 0));
    //this->_field->setOutlineThickness(2);

    // TODO better using of constants
    for(int i = 1; i < 16; i++)
    {
        for(int j = 1; j < 9; j++)
        {
            sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(1, 1));
            r.setPosition(i * 64, j * 64);
            r.setFillColor(sf::Color(181, 137, 0));
            this->_fieldPoints.push_back(r);
        }
    }

    this->_square = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(64, 64)));
    this->_square->setFillColor(sf::Color(147, 161, 161));
    this->_square->setPosition(64, 64);

    this->_time = std::unique_ptr<sf::Text>(new sf::Text("", *this->_sourceSansPro, 40));
    this->_time->setColor(sf::Color(42, 161, 152));
    this->_time->setPosition(sf::Vector2f(30, 30));

    this->_enemies.push_back(LittleEnemyEntity(sf::Vector2f(32, 32), *this->_sourceSansPro));

    this->_isActive = true;
}

void MatchState::stop()
{
    DebugOutput::gameState("MatchState", "stop");

    this->_sourceSansPro.reset();
    this->_clock.reset();
    this->_additionalTime.reset();
    this->_field.reset();
    this->_fieldPoints.clear();
    this->_time.reset();

    this->_enemies.empty();

    this->_isActive = false;
}

void MatchState::pause()
{
    DebugOutput::gameState("MatchState", "pause");

    *this->_additionalTime += this->_clock->getElapsedTime();

    this->_isPaused = true;
}

void MatchState::resume()
{
    DebugOutput::gameState("MatchState", "resume");

    this->_clock->restart();

    this->_isPaused = false;
}

void MatchState::handleEvent(const sf::Event &event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Q)
            this->changeState(StateChangeType::PopState);
        else if(event.key.code == sf::Keyboard::P)
        {
            if(!this->isPaused())
                this->pause();
            else
                this->resume();
        }
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
    // little dirty fps hack...

    this->_time->setString(intToString(1.f / this->_clock->getElapsedTime().asSeconds()));

    this->_clock->restart();
}

void MatchState::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->_field);
    for(sf::Drawable &d: this->_fieldPoints)
    {
        renderTarget.draw(d);
    }
    renderTarget.draw(*this->_time);
    renderTarget.draw(*this->_square);
    for(sf::Drawable &d: this->_enemies)
    {
        renderTarget.draw(d);
    }
}

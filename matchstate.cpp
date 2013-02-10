#include "matchstate.h"

MatchState::MatchState(sf::RenderTarget *renderTarget) : GameState(renderTarget)
{
    std::cout << "[MatchState] initialization" << std::endl;
}

MatchState::~MatchState()
{
    std::cout << "[MatchState] cleanup" << std::endl;
}

void MatchState::start()
{
    std::cout << "[MatchState] start" << std::endl;

    this->_sourceSansPro = std::unique_ptr<sf::Font>(new sf::Font());
    this->_sourceSansPro->loadFromFile("SourceSansPro-Light.ttf");

    this->_clock = std::unique_ptr<sf::Clock>(new sf::Clock());
    this->_clock->restart();

    this->_additionalTime = std::unique_ptr<sf::Time>(new sf::Time());

    //this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(700, 400)));
    // TODO
    this->_field = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(1920, 1080)));
    this->_field->setFillColor(sf::Color(253, 246, 227));
    //this->_field->setOutlineColor(sf::Color(181, 137, 0));
    //this->_field->setOutlineThickness(10);

    this->_square = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(100, 100)));
    this->_square->setFillColor(sf::Color(253, 246, 227));
    this->_square->setOutlineColor(sf::Color(181, 137, 0));
    this->_square->setOutlineThickness(10);
    this->_square->setPosition(910, 490);

    this->_time = std::unique_ptr<sf::Text>(new sf::Text("", *this->_sourceSansPro, 40));
    this->_time->setColor(sf::Color(42, 161, 152));
    this->_time->setPosition(sf::Vector2f(0, -45));

    this->_isActive = true;
}

void MatchState::stop()
{
    std::cout << "[MatchState] stop" << std::endl;

    this->_sourceSansPro.reset();
    this->_clock.reset();
    this->_additionalTime.reset();
    this->_field.reset();
    this->_time.reset();

    this->_isActive = false;
}

void MatchState::pause()
{
    std::cout << "[MatchState] pause" << std::endl;

    *this->_additionalTime += this->_clock->getElapsedTime();

    this->_isPaused = true;
}

void MatchState::resume()
{
    std::cout << "[MatchState] resume" << std::endl;

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
    if((static_cast<float>(x) / static_cast<float>(y)) <= (16.f / 9.f))
    {
        float z = (960.f * y) / x - 540.f;
        return sf::View(sf::Vector2f(960, 540), sf::Vector2f(1920, (1080 + (2 * z))));
    }
    else
    {
        float z = (540.f * x) / y - 960.f;
        return sf::View(sf::Vector2f(960, 540), sf::Vector2f((1920 + (2 * z)), 1080));
    }
}

void MatchState::update()
{
    this->_time->setString(intToString((this->_clock->getElapsedTime() + *this->_additionalTime).asSeconds()));
}

void MatchState::draw(sf::RenderTarget &renderTarget)
{
    //renderTarget.clear(sf::Color(253, 246, 227));
    renderTarget.draw(*this->_field);
    renderTarget.draw(*this->_time);
    renderTarget.draw(*this->_square);
}

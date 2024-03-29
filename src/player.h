#pragma once

#include <direction.h>

#include <SFML/Graphics.hpp>
#include <stdexcept>

#include <vector>

class Player : public sf::Drawable
{
public:
    struct PlayerLineElement
    {
        PlayerLineElement(sf::RectangleShape line, Direction direction) : line(line), direction(direction) {}
        float getLength()
        {
            if (this->direction == Direction::Up || this->direction == Direction::Down)
                return this->line.getSize().y;
            else
                return this->line.getSize().x;
        }

        sf::RectangleShape line;
        Direction direction;
    };

    Player(const sf::Vector2f startingPosition, const Direction direction, const sf::Color color = sf::Color(220, 50, 47), const float maximumLength = 128.f);

    void changeDirection(const Direction direction);

    Direction getDirection();
    float getLength();
    float getMaximumLength();
    bool isActive();
    bool isAlive();

    void setLifeStatus(bool isAlive);
    void setMaximumLength(float maximumLength);

    void update(const sf::Time &time);

    bool firstElementIntersectsWithBoundaries();
    bool firstElementIntersectsWithPlayer();
    bool firstElementIntersectsWith(const sf::FloatRect &rect);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void adjustLength();

    bool m_isActive;
    bool m_isAlive;
    float m_maximumLength;
    std::vector<PlayerLineElement> m_lines;
};

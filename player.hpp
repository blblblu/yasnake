#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "direction.hpp"

class Player : public sf::Drawable
{
public:
    struct PlayerLineElement //TODO: besserer Name
    {
        PlayerLineElement(sf::RectangleShape line, Direction direction) : line(line), direction(direction){}
        float getLength()
        {
            if(this->direction == Direction::Up || this->direction == Direction::Down)
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

    void update(const sf::Time &time);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void adjustLength();

    bool isAlive;
    float m_maximumLength;
    std::vector<PlayerLineElement> m_lines;
};

#endif // PLAYER_H

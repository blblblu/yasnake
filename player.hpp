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
        sf::RectangleShape line;
        Direction direction;
    };

    Player(sf::Vector2f startingPosition, Direction direction, sf::Color color = sf::Color::Black);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Color m_color;
    Direction m_direction;
    std::vector<PlayerLineElement> m_lines;
};

#endif // PLAYER_H

#include "player.hpp"

Player::Player(sf::Vector2f startingPosition, Direction direction, sf::Color color)
{
    this->m_color = color;
    this->m_direction = direction;
    sf::RectangleShape line;
    line.setFillColor(color);
    if(direction == Up || direction == Down)
    {
        line.setSize(sf::Vector2f(8, 0));
        line.setPosition(startingPosition - sf::Vector2f(4, 0)); //TODO: Rechnungen kontrollieren
    }
    else
    {
        line.setSize(sf::Vector2f(0, 8));
        line.setPosition(startingPosition - sf::Vector2f(0, 4)); //TODO: Rechnungen kontrollieren
    }
    this->m_lines.push_back(PlayerLineElement(line, direction));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // TODO: mit for_each-Schleife o.ä. lösen
    for(unsigned int i = 0; i < this->m_lines.size(); i++)
    {
        target.draw(this->m_lines[i].line, states);
    }
}

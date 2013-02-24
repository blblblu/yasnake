#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

class GameEntity : public sf::Drawable
{
public:
    GameEntity(std::string text, sf::Color color);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states);

    sf::RectangleShape _shape;
    sf::Text _text;
};

#endif // GAMEENTITY_H

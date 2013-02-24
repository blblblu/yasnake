#include "gameentity.h"

GameEntity::GameEntity(std::string text, sf::Color color)
{
    this->_shape.setFillColor(color * sf::Color(128, 128, 128));
    this->_shape.setOutlineColor(color);
    this->_shape.setOutlineThickness(2);
}

void GameEntity::draw(sf::RenderTarget &target, sf::RenderStates states)
{
    target.draw(this->_shape);
}

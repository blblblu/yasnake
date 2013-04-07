#include "littleenemyentity.h"

LittleEnemyEntity::LittleEnemyEntity(const sf::Vector2f &position, const sf::Font &font) : EnemyEntity(position, font)
{
    this->_shape.setFillColor(sf::Color(232, 187, 46));
    this->_shape.setOutlineColor(sf::Color(181, 137, 0));
    this->_shape.setOutlineThickness(1);
}

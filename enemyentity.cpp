#include "enemyentity.h"

EnemyEntity::EnemyEntity(const sf::Vector2f &position, const sf::Font &font) : _shape(sf::Vector2f(32, 32)), _text("", font, 16)
{
    this->_shape.setPosition(position - sf::Vector2f(16, 16)); // damit die gegebene Position als Mittelpunkt angesehen wird
}

void EnemyEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->_shape, states);
    target.draw(this->_text, states);
}

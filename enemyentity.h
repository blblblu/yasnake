#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

class EnemyEntity : public sf::Drawable
{
public:
    EnemyEntity(const sf::Vector2f &position, const sf::Font &font);
    virtual ~EnemyEntity(){}

    //virtual void attacked(int damage) = 0;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    sf::RectangleShape _shape;
    sf::Text _text;
};

#endif // ENEMYENTITY_H

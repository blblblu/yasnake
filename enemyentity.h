#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class EnemyEntity : public sf::Drawable
{
public:
    EnemyEntity();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

#endif // ENEMYENTITY_H

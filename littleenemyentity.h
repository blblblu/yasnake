#ifndef LITTLEENEMYENTITY_H
#define LITTLEENEMYENTITY_H

#include "enemyentity.h"

class LittleEnemyEntity : public EnemyEntity
{
public:
    LittleEnemyEntity(const sf::Vector2f &position, const sf::Font &font);
};

#endif // LITTLEENEMYENTITY_H

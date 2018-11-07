#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Entity.hpp"

class EnemyEntity : public Entity
{
    public:
        enum Type
        {
            bat,
            spider,
            bouftou
        };

        EnemyEntity(oe::EntityManager& manager,Type enemyEntityType);
        ~EnemyEntity();

        virtual void update(oe::Time dt);
};

#endif // ENEMYENTITY_HPP

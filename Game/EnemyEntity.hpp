#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Entity.hpp"

class EnemyEntity : public Entity
{
    public:
        EnemyEntity(oe::EntityManager& manager);
        ~EnemyEntity();

        virtual void update(oe::Time dt);

    private:

};

#endif // ENEMYENTITY_HPP

#ifndef BOUFTOUENTITY_HPP
#define BOUFTOUENTITY_HPP

#include "EnemyEntity.hpp"
#include "../Engine/Core/World.hpp"
#include "Entity.hpp"
#include "Room.hpp"

class BouftouEntity : public EnemyEntity
{
    public:
        BouftouEntity(oe::EntityManager& manager);
        ~BouftouEntity();

        virtual void update(oe::Time dt);

};

#endif // BOUFTOUENTITY_HPP

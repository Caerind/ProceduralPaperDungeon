#ifndef SPIDERENTITY_HPP
#define SPIDERENTITY_HPP

#include "EnemyEntity.hpp"
#include "../Engine/Core/World.hpp"
#include "Entity.hpp"
#include "Room.hpp"

class SpiderEntity : public EnemyEntity
{
    public:
        SpiderEntity(oe::EntityManager& manager, Room* room);
        ~SpiderEntity();

        virtual void update(oe::Time dt);
};

#endif // SPIDERENTITY_HPP

#ifndef BATENTITY_HPP
#define BATENTITY_HPP

#include "EnemyEntity.hpp"
#include "../Engine/Core/World.hpp"
#include "Entity.hpp"
#include "Room.hpp"
#include "Projectile.hpp"

class BatEntity : public EnemyEntity
{
    public:
        BatEntity(oe::EntityManager& manager);
        ~BatEntity();

        virtual void update(oe::Time dt);
};

#endif // BATENTITY_HPP

#include "Entity.hpp"

Entity::Entity(oe::EntityManager& manager)
    : oe::Entity(manager)
    , mSprite(*this)
{
}

Entity::~Entity()
{
}

void Entity::update(oe::Time dt)
{
}

#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity(oe::EntityManager& manager)
    : Entity(manager)
    , mAction(*this)
{
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::update(oe::Time dt)
{
}

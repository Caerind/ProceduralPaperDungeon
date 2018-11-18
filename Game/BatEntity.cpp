#include "BatEntity.hpp"
#include "Room.hpp"

BatEntity::BatEntity(oe::EntityManager& manager)
    : EnemyEntity(manager, EnemyEntity::Bat)
{
    mLifeMax = 20;
    mLife = mLifeMax;
    mStrength = 10;
    mMovementSpeed = 100;
    mFireSpeed = 200.0f;
    mFireLimit = oe::seconds(0.5f);
    mFireCooldown = mFireLimit;
    mSprite.setTextureRect(sf::IntRect(99, 19, 123, 44));
    mSprite.setPositionZ(10.0f);
    mSprite.setPosition(-61.5f, -55.0f);
}

BatEntity::~BatEntity()
{
}

void BatEntity::update(oe::Time dt)
{
    if (mRoom != nullptr)
    {
        mFireCooldown += dt;
        oe::Vector2 delta = mRoom->getPlayerHandle()->getPosition() - getPosition();
        oe::Vector2 mvt = delta.normalize();
        //bool moved =
        tryMove(dt, mvt);
        shoot();
    }
}

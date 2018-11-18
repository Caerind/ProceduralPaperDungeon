#include "SpiderEntity.hpp"
#include "Room.hpp"
#include "Projectile.hpp"

SpiderEntity::SpiderEntity(oe::EntityManager& manager, Room* room)
    : EnemyEntity(manager, EnemyEntity::Spider, mRoom)
{
    mLifeMax = 25;
    mLife = mLifeMax;
    mStrength = 10;
    mMovementSpeed = 100;
    mFireSpeed = 200.0f;
    mFireLimit = oe::seconds(0.4f);
    mFireCooldown = mFireLimit;
    mSprite.setTextureRect(sf::IntRect(258, 20, 93, 46));
    mSprite.setPositionZ(10.0f);
    mSprite.setPosition(-46.5f, -41.0f);
}

SpiderEntity::~SpiderEntity()
{
}

void SpiderEntity::update(oe::Time dt)
{
    /*
    mFireCooldown += dt;
    oe::Vector2 delta = mRoom->getPlayerHandle()->getPosition() - getPosition();
    oe::Vector2 mvt = delta.normalize();
    //bool moved =
    tryMove(dt, mvt);
    shoot();
    */
}

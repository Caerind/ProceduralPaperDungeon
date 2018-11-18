#include <iostream>

#include "BouftouEntity.hpp"
#include "Room.hpp"
#include "Projectile.hpp"

BouftouEntity::BouftouEntity(oe::EntityManager& manager)
    : EnemyEntity(manager, EnemyEntity::Bouftou)
{
    mLifeMax = 50;
    mLife = mLifeMax;
    mStrength = 10;
    mMovementSpeed = 10;
    mFireSpeed = 200.0f;
    mFireLimit = oe::seconds(0.5f);
    mFireCooldown = mFireLimit;
    mSprite.setTextureRect(sf::IntRect(373, 15, 71, 50));
    mSprite.setPositionZ(10.0f);
    mSprite.setPosition(-35.5f, -50.0f);
}

BouftouEntity::~BouftouEntity()
{
}

void BouftouEntity::update(oe::Time dt)
{
    /*
    mFireCooldown += dt;
    oe::Vector2 posPlayer = mRoom->getPlayerHandle()->getPosition();
    if (shoot())
    {

    }
    else
    {
        oe::Vector2 delta = posPlayer - getPosition();
        oe::Vector2 mvt = delta;
        tryMove(dt, delta);
    }
    */
}

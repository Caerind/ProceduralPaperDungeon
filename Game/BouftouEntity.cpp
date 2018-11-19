#include <iostream>

#include "BouftouEntity.hpp"
#include "Room.hpp"
#include "Projectile.hpp"
#include "GameConfig.hpp"

BouftouEntity::BouftouEntity(oe::EntityManager& manager)
    : EnemyEntity(manager, EnemyEntity::Bouftou)
{
    mLifeMax = 50;
    mLife = mLifeMax;
    mStrength = 10;
    mMovementSpeed = 400;
    mFireSpeed = 400.0f;
    mFireLimit = oe::seconds(2.5f);
    mFireCooldown = mFireLimit;
    mSprite.setTextureRect(sf::IntRect(373, 15, 71, 50));
    mSprite.setPositionZ(10.0f);
    mSprite.setPosition(-35.5f, -50.0f);
    mPosPlayer = oe::Vector2(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

BouftouEntity::~BouftouEntity()
{
    updateData();
}

void BouftouEntity::update(oe::Time dt)
{
    if (mRoom != nullptr)
    {
        mFireCooldown += dt;
        if (shoot())
        {
            mPosPlayer = mRoom->getPlayerHandle()->getPosition();
        }
        else
        {
            oe::Vector2 delta = mPosPlayer - getPosition();
            oe::Vector2 mvt = delta.normalize();
            tryMove(dt, mvt);
        }
    }
}

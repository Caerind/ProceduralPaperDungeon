#include "EnemyEntity.hpp"

#include "../Engine/Math/Random.hpp"
#include "../Engine/Application/Application.hpp"

EnemyEntity::EnemyEntity(oe::EntityManager& manager, EnemyEntity::Type enemyEntityType)
    : Entity(manager)
{
    // First load background
    mSprite.setTexture(mTilesetTexture);
    if(enemyEntityType == bat)
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
    else if(enemyEntityType == spider)
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
    else if(enemyEntityType == bouftou)
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

    F32 x = oe::Random::get<F32>(120, 944);
    F32 y = oe::Random::get<F32>(20, 648);

    setPosition(x, y);
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::update(oe::Time dt)
{
    mFireCooldown += dt;
}

#include "EnemyEntity.hpp"

#include "../Engine/Math/Random.hpp"
#include "../Engine/Application/Application.hpp"

#include "Projectile.hpp"

EnemyEntity::EnemyEntity(oe::EntityManager& manager, EnemyEntity::Type enemyEntityType)
    : Entity(manager)
    , mRoom(nullptr)
{
    // First load background
    mSprite.setTexture(mTilesetTexture);
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::setRoom(Room* room)
{
    mRoom = room;
}

bool EnemyEntity::shoot()
{
	if (mFireCooldown >= mFireLimit && mRoom != nullptr && mRoom->getPlayerHandle().isValid())
	{
        oe::Vector2 delta = mRoom->getPlayerHandle()->getPosition() - getPosition();
		delta.normalize();

		mRoom->addEntity(getManager().createEntity<Projectile>(getPosition(), delta, mStrength, mFireSpeed));

		mFireCooldown = oe::Time::Zero;

		return true;
	}
	return false;
}

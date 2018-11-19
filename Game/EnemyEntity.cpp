#include "EnemyEntity.hpp"

#include "../Engine/Math/Random.hpp"
#include "../Engine/Application/Application.hpp"

#include "Projectile.hpp"

EnemyEntity::EnemyEntity(oe::EntityManager& manager, EnemyEntity::Type enemyEntityType)
    : Entity(manager)
    , mRoom(nullptr)
    , mIndex(0)
{
    // First load background
    mSprite.setTexture(mTilesetTexture);
}

EnemyEntity::~EnemyEntity()
{
    updateData();
}

void EnemyEntity::setRoom(Room* room)
{
    mRoom = room;
}

void EnemyEntity::setIndex(unsigned int index)
{
    mIndex = index;
}

unsigned int EnemyEntity::getIndexInData() const
{
    return mIndex;
}

void EnemyEntity::updateData()
{
    if (mRoom != nullptr)
    {
        if (mLife <= 0 && mLifeMax > 0)
        {
            mRoom->removeEnemyWithIndex(mIndex);
        }
        else
        {
            mRoom->updateEnemyPosition(mIndex, getPosition());
        }
    }
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

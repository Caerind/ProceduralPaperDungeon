#include "Projectile.hpp"

#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

Projectile::Projectile(oe::EntityManager& manager, const oe::Vector2& position, const oe::Vector2& direction, U32 strength, F32 projectileSpeed)
    : oe::Entity(manager)
    , mSprite(*this)
    , mDirection(direction)
{
    setPosition(position);

    mStrength = strength;
    mProjectileSpeed = projectileSpeed;

    // Load fire texture if not loaded
    if (mFireTexture == 0)
    {
        mFireTexture = manager.getWorld().getApplication().getTextures().create("FireTexture", oe::TextureLoader::loadFromFile(TEXTURE_FIRE));
    }

    mSprite.setTexture(mFireTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 14, 12));
    mSprite.setPositionZ(8.0f);
    mSprite.setPosition(-7, -6);
}

void Projectile::update(oe::Time dt)
{
	//oe::DebugDraw::drawRect(getAABB());

	oe::Vector2 mvt(mDirection);
	mvt.setLength(dt.asSeconds() * mProjectileSpeed);
	oe::Vector2 nextPos = getPosition() + mvt;

	bool collision = false;

	if (nextPos.x < 80 || nextPos.x > WINSIZEX-80 || nextPos.y < 80 || nextPos.y > WINSIZEY-80)
    {
        collision = true;
    }

	if (!collision)
	{
		setPosition(nextPos);
	}
	else
	{
        kill();
	}
}

oe::ResourceId Projectile::mFireTexture = 0;

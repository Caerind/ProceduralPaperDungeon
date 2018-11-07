#include "Entity.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "GameConfig.hpp"

Entity::Entity(oe::EntityManager& manager)
    : oe::Entity(manager)
    , mSprite(*this)
{

    // Load Tileset texture if not loaded
    if (mTilesetTexture == 0)
    {
        mTilesetTexture = manager.getWorld().getApplication().getTextures().create("TilesetTexture", oe::TextureLoader::loadFromFile(TEXTURE_TILESET));
    }

}

Entity::~Entity()
{
}

void Entity::update(oe::Time dt)
{
}

bool Entity::determineMovement(oe::Vector2& mvt)
{
	return false;
}

bool Entity::tryMove(oe::Time dt, oe::Vector2& mvt)
{
	mvt.setLength(dt.asSeconds() * mMovementSpeed);
	oe::Vector2 nextPos = getPosition() + mvt;
	bool collision = false;

	if (nextPos.x < 110 || nextPos.x > WINSIZEX-110 || nextPos.y < 80 || nextPos.y > WINSIZEY-80)
    {
        collision = true;
    }
	if (!collision)
	{
		setPosition(nextPos);
	}
	else
	{
		mvt.makeZero();
	}

	return !collision;
}
oe::ResourceId Entity::mTilesetTexture = 0;

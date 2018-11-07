#include "Stair.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "GameConfig.hpp"

Stair::Stair(oe::EntityManager& manager)
    : oe::Entity(manager)
    , mStair(*this)
{
    // Load room things texture if not loaded
    if (mRoomThingsTexture == 0)
    {
        mRoomThingsTexture = manager.getWorld().getApplication().getTextures().create("roomThingsTextureStair", oe::TextureLoader::loadFromFile(TEXTURE_ROOM_THINGS));
    }

    // Load stair
    mStair.setTexture(mRoomThingsTexture);
    mStair.setTextureRect(sf::IntRect(180, 0, 60, 80));
    mStair.setPositionZ(-20.0f);
    mStair.setPosition((WINSIZEX/2) - 30, (WINSIZEY/2) - 60);
}

oe::ResourceId Stair::mRoomThingsTexture = 0;

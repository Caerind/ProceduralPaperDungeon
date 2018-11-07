#include "Chest.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "GameConfig.hpp"

Chest::Chest(oe::EntityManager& manager, RoomData& roomData)
    : oe::Entity(manager)
    , mData(roomData)
    , mChest(*this)
{
    // Load room things texture if not loaded
    if (mRoomThingsTexture == 0)
    {
        mRoomThingsTexture = manager.getWorld().getApplication().getTextures().create("roomThingsTextureChest", oe::TextureLoader::loadFromFile(TEXTURE_ROOM_THINGS));
    }

    // Load stair
    mChest.setTexture(mRoomThingsTexture);
    mChest.setTextureRect(sf::IntRect(60, 0, 60, 80));
    mChest.setPositionZ(-20.0f);
    mChest.setPosition((WINSIZEX/2) - 30, (WINSIZEY/2) - 60);
}

oe::ResourceId Chest::mRoomThingsTexture = 0;

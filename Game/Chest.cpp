#include "Chest.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "GameConfig.hpp"
#include "PlayerEntity.hpp"

Chest::Chest(oe::EntityManager& manager, RoomData& roomData, const oe::EntityHandle& playerHandle)
    : oe::Entity(manager)
    , mData(roomData)
    , mPlayerHandle(playerHandle)
    , mChest(*this)
    , mOpen(mData.isChestOpen())
{
    // Load room things texture if not loaded
    if (mRoomThingsTexture == 0)
    {
        mRoomThingsTexture = manager.getWorld().getApplication().getTextures().create("roomThingsTextureChest", oe::TextureLoader::loadFromFile(TEXTURE_ROOM_THINGS));
    }

    // Load stair
    mChest.setTexture(mRoomThingsTexture);
    if (mOpen)
    {
        mChest.setTextureRect(sf::IntRect(120, 0, 60, 80));
    }
    else
    {
        mChest.setTextureRect(sf::IntRect(60, 0, 60, 80));
    }
    mChest.setPositionZ(-20.0f);
    mChest.setPosition((WINSIZEX/2) - 30, (WINSIZEY/2) - 60);
}

bool Chest::isOpen() const
{
    return mOpen;
}

void Chest::open()
{
    if (!mOpen)
    {
        if (LOG_IN_CONSOLE)
        {
            printf("Opening the chest\n");
        }
        mOpen = true;
        mData.openChest();
        mChest.setTextureRect(sf::IntRect(120, 0, 60, 80));
        mPlayerHandle->getAs<PlayerEntity>()->increase();
    }
}

oe::ResourceId Chest::mRoomThingsTexture = 0;

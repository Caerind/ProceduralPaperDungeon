#include "Background.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "GameConfig.hpp"

Background::Background(oe::EntityManager& manager, RoomData& roomData)
    : oe::Entity(manager)
    , mRoomData(roomData)
    , mBackground(*this)
    , mWall(*this)
    , mDoors()
{
    // Load background texture if not loaded
    if (mBackgroundTexture == 0)
    {
        mBackgroundTexture = manager.getWorld().getApplication().getTextures().create("backgroundTexture", oe::TextureLoader::loadFromFile(TEXTURE_BACKGROUND));
    }

    // Load wall texture if not loaded
    if (mWallTexture == 0)
    {
        mWallTexture = manager.getWorld().getApplication().getTextures().create("wallTexture", oe::TextureLoader::loadFromFile(TEXTURE_WALL));
    }

    // Load room things texture if not loaded
    if (mRoomThingsTexture == 0)
    {
        mRoomThingsTexture = manager.getWorld().getApplication().getTextures().create("roomThingsTexture", oe::TextureLoader::loadFromFile(TEXTURE_ROOM_THINGS));
    }

    // Load stain texture if not loaded
    if (mStainsTexture == 0)
    {
        mStainsTexture = manager.getWorld().getApplication().getTextures().create("stainTexture", oe::TextureLoader::loadFromFile(TEXTURE_STAINS));
    }

    // First load background
    mBackground.setTexture(mBackgroundTexture);
    mBackground.setPositionZ(-20.0f);
    mBackground.setPosition(80.0f, 80.0f);

    // Then load background
    mWall.setTexture(mWallTexture);
    mWall.setPositionZ(-10.0f);
    mWall.setPosition(0.0f, 0.0f);

    // Then load doors depending on door flags
    if ((mRoomData.getDoorFlags() & RoomData::DoorFlags::Top) > 0)
    {
        std::unique_ptr<oe::SpriteComponent> sprite = std::unique_ptr<oe::SpriteComponent>(new oe::SpriteComponent(*this));
        sprite->setTexture(mRoomThingsTexture);
        sprite->setPositionZ(-5.0f);
        sprite->setPosition((WINSIZEX / 2) - 30, 0);
        mDoors.push_back(std::move(sprite));
    }
    if ((mRoomData.getDoorFlags() & RoomData::DoorFlags::Right) > 0)
    {
        std::unique_ptr<oe::SpriteComponent> sprite = std::unique_ptr<oe::SpriteComponent>(new oe::SpriteComponent(*this));
        sprite->setTexture(mRoomThingsTexture);
        sprite->setPositionZ(-5.0f);
        sprite->setPosition(WINSIZEX, (WINSIZEY / 2) - 30);
        sprite->setRotation(90);
        mDoors.push_back(std::move(sprite));
    }
    if ((mRoomData.getDoorFlags() & RoomData::DoorFlags::Bottom) > 0)
    {
        std::unique_ptr<oe::SpriteComponent> sprite = std::unique_ptr<oe::SpriteComponent>(new oe::SpriteComponent(*this));
        sprite->setTexture(mRoomThingsTexture);
        sprite->setPositionZ(-5.0f);
        sprite->setPosition((WINSIZEX / 2) - 30 + 60, WINSIZEY);
        sprite->setRotation(180);
        mDoors.push_back(std::move(sprite));
    }
    if ((mRoomData.getDoorFlags() & RoomData::DoorFlags::Left) > 0)
    {
        std::unique_ptr<oe::SpriteComponent> sprite = std::unique_ptr<oe::SpriteComponent>(new oe::SpriteComponent(*this));
        sprite->setTexture(mRoomThingsTexture);
        sprite->setPositionZ(-5.0f);
        sprite->setPosition(0, (WINSIZEY / 2) + 30);
        sprite->setRotation(270);
        mDoors.push_back(std::move(sprite));
    }

    // If specified in room data, add things on the floor
    for (unsigned int i = 0; i < mRoomData.getStainCount(); i++)
    {
        const RoomData::Stain& stain = mRoomData.getStain(i);
        std::unique_ptr<oe::SpriteComponent> sprite = std::unique_ptr<oe::SpriteComponent>(new oe::SpriteComponent(*this));
        sprite->setTexture(mStainsTexture);
        sprite->setTextureRect(sf::IntRect(200 * stain.type, 0, 200, 200));
        sprite->setPositionZ(-15.0f);
        sprite->setPosition(stain.x, stain.y);
        sprite->setRotation(stain.angle);
        sprite->setScale(stain.scale, stain.scale);
        mStains.push_back(std::move(sprite));
    }
}

oe::ResourceId Background::mBackgroundTexture = 0;
oe::ResourceId Background::mWallTexture = 0;
oe::ResourceId Background::mRoomThingsTexture = 0;
oe::ResourceId Background::mStainsTexture = 0;

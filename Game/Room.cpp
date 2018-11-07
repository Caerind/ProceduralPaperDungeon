#include "Room.hpp"

#include "Background.hpp"
#include "EnemyEntity.hpp"
#include "Stair.hpp"
#include "Chest.hpp"

Room::Room(oe::World& world, RoomData& roomData)
    : mWorld(world)
    , mData(roomData)
    , mEntities()
{
    printf("\nRoom %d (%d,%d)\n", mData.getRoomIndex(), mData.getRoomX(), mData.getRoomY());

    // First load background of the room
	mEntities.push_back(mWorld.getEntityManager().createEntity<Background>(mData));

    // If any add enemy
    for (unsigned int i = 0; i < mData.getEnemyCount(); i++)
    {
        const RoomData::Enemy& enemyData = mData.getEnemy(i);
        oe::EntityHandle enemyHandle = mWorld.getEntityManager().createEntity<EnemyEntity>((EnemyEntity::Type)enemyData.type);
        enemyHandle->setPosition(enemyData.x, enemyData.y);
        mEntities.push_back(enemyHandle);
    }

    // If chest add chest
    if (mData.isChestRoom())
    {
        mEntities.push_back(mWorld.getEntityManager().createEntity<Chest>(mData));
        printf("Chest\n");
    }

    // If stair add stair
    if (mData.isStairsRoom())
    {
        mEntities.push_back(mWorld.getEntityManager().createEntity<Stair>());
        printf("Stair\n");
    }

    // Others things...
}

Room::~Room()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mWorld.getEntityManager().killEntity(mEntities[i]);
    }
}

bool Room::hasDoor(RoomData::DoorFlags doorFlag) const
{
    return (mData.getDoorFlags() & doorFlag) != 0;
}

unsigned int Room::getRoomIndex(RoomData::DoorFlags doorFlag) const
{
    return mData.getConnectionIndex(doorFlag);
}

unsigned int Room::getIndex() const
{
    return mData.getRoomIndex();
}

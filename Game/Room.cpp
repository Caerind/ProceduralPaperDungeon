#include "Room.hpp"

#include "Background.hpp"
#include "EnemyEntity.hpp"
#include "Stair.hpp"
#include "Chest.hpp"
#include "GameConfig.hpp"
#include "BatEntity.hpp"
#include "SpiderEntity.hpp"
#include "BouftouEntity.hpp"

Room::Room(oe::World& world, RoomData& roomData, const oe::EntityHandle& playerHandle)
    : mWorld(world)
    , mData(roomData)
    , mPlayerHandle(playerHandle)
    , mStairs(mData.isStairsRoom())
    , mClosedChest(false)
    , mEntities()
{
    if (LOG_IN_CONSOLE)
    {
        printf("\nRoom %d (%d,%d)\n", mData.getRoomIndex(), mData.getRoomX(), mData.getRoomY());
    }

    // First load background of the room
	mEntities.push_back(mWorld.getEntityManager().createEntity<Background>(mData));

    // If any add enemy
    for (unsigned int i = 0; i < mData.getEnemyCount(); i++)
    {
        const RoomData::Enemy& enemyData = mData.getEnemy(i);

        printf("RoomThis %x\n", this);

        oe::EntityHandle enemyHandle;
        switch (enemyData.type)
        {
            case EnemyEntity::Bat:
                enemyHandle = mWorld.getEntityManager().createEntity<BatEntity>();
                if (LOG_IN_CONSOLE)
                {
                    printf("Bat\n");
                }
                enemyHandle.getAs<BatEntity>()->setRoom(this);
                break;

            case EnemyEntity::Spider:
                enemyHandle = mWorld.getEntityManager().createEntity<SpiderEntity>();
                enemyHandle.getAs<SpiderEntity>()->setRoom(this);
                if (LOG_IN_CONSOLE)
                {
                    printf("Spider\n");
                }
                break;

            case EnemyEntity::Bouftou:
                enemyHandle = mWorld.getEntityManager().createEntity<BouftouEntity>();
                enemyHandle.getAs<BouftouEntity>()->setRoom(this);
                if (LOG_IN_CONSOLE)
                {
                    printf("Bouftou\n");
                }
                break;

            default: break;
        }

        enemyHandle->setPosition(enemyData.x, enemyData.y);
        mEntities.push_back(enemyHandle);

    }

    // If chest add chest
    if (mData.isChestRoom())
    {
        mEntities.push_back(mWorld.getEntityManager().createEntity<Chest>(mData));
        if (LOG_IN_CONSOLE)
        {
            printf("Chest\n");
        }
    }

    // If stair add stair
    if (mData.isStairsRoom())
    {
        mEntities.push_back(mWorld.getEntityManager().createEntity<Stair>());
        if (LOG_IN_CONSOLE)
        {
            printf("Stair\n");
        }
    }
}

Room::~Room()
{
    // TODO : Update state of the room

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mWorld.getEntityManager().killEntity(mEntities[i]);
    }
}

bool Room::update()
{
    if (mClosedChest)
    {
        // TODO : Open Chest
    }

    if (mStairs && mPlayerHandle.isValid())
    {
        oe::Vector2 centerOfRoom(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
        float delta = oe::Vector2::distance(centerOfRoom, mPlayerHandle->getPosition());
        return delta < 40.0f;
    }
    return false;
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

void Room::addEntity(const oe::EntityHandle& entityHandle)
{
    mEntities.push_back(entityHandle);
}

const oe::EntityHandle& Room::getPlayerHandle() const
{
    return mPlayerHandle;
}

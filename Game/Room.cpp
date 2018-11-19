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
    , mChest(nullptr)
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
        switch (enemyData.type)
        {
            case EnemyEntity::Bat:
                createEnemy<BatEntity>(enemyData);
                if (LOG_IN_CONSOLE)
                {
                    printf("Bat\n");
                }
                break;

            case EnemyEntity::Spider:
                createEnemy<SpiderEntity>(enemyData);
                if (LOG_IN_CONSOLE)
                {
                    printf("Spider\n");
                }
                break;

            case EnemyEntity::Bouftou:
                createEnemy<BouftouEntity>(enemyData);
                if (LOG_IN_CONSOLE)
                {
                    printf("Bouftou\n");
                }
                break;

            default: break;
        }
    }

    // If chest add chest
    if (mData.isChestRoom())
    {
        oe::EntityHandle chestHandle = mWorld.getEntityManager().createEntity<Chest>(mData, mPlayerHandle);
        mEntities.push_back(chestHandle);
        mChest = chestHandle->getAs<Chest>();
        if (LOG_IN_CONSOLE)
        {
            if (mChest->isOpen())
            {
                printf("Chest Open\n");
            }
            else
            {
                printf("Chest Closed\n");
            }
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
}

bool Room::update()
{
    if (mPlayerHandle.isValid() && ((mChest != nullptr && !mChest->isOpen()) || mStairs))
    {
        oe::Vector2 centerOfRoom(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
        float delta = oe::Vector2::distance(centerOfRoom, mPlayerHandle->getPosition());
        if (mChest != nullptr && !mChest->isOpen() && delta < 50.0f)
        {
            mChest->open();
        }
        if (mStairs)
        {
            return delta < 40.0f;
        }
    }
    return false;
}

void Room::clear()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mWorld.getEntityManager().killEntity(mEntities[i]);
    }
    mWorld.getEntityManager().destroyEntities();
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

void Room::removeEnemyWithIndex(unsigned int index)
{
    mData.removeEnemy(index);
}

void Room::updateEnemyPosition(unsigned int index, const oe::Vector2& position)
{
    RoomData::Enemy* enemy = mData.getEnemyPtr(index);
    if (enemy != nullptr)
    {
        enemy->x = position.x;
        enemy->y = position.y;
    }
}

const oe::EntityHandle& Room::getPlayerHandle() const
{
    return mPlayerHandle;
}

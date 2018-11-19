#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>

#include "../Engine/Core/World.hpp"

#include "RoomData.hpp"
#include "Chest.hpp"

class Room
{
    public:
        Room(oe::World& world, RoomData& roomData, const oe::EntityHandle& playerHandle);
        ~Room();

        bool update();

        void clear();

        bool hasDoor(RoomData::DoorFlags doorFlag) const;
        unsigned int getRoomIndex(RoomData::DoorFlags doorFlag) const;

        const std::string& getSeed() const;
        unsigned int getIndex() const;

        void addEntity(const oe::EntityHandle& entityHandle);
        void removeEnemyWithIndex(unsigned int index);
        void updateEnemyPosition(unsigned int index, const oe::Vector2& position);

        const oe::EntityHandle& getPlayerHandle() const;

        template <typename T>
        void createEnemy(const RoomData::Enemy& enemyData);

        typedef std::unique_ptr<Room> Ptr;

    private:
        oe::World& mWorld;
        RoomData& mData;
        const oe::EntityHandle& mPlayerHandle;

        bool mStairs;
        Chest* mChest;

        std::vector<oe::EntityHandle> mEntities;
};

template <typename T>
void Room::createEnemy(const RoomData::Enemy& enemyData)
{
    oe::EntityHandle enemyHandle;
    enemyHandle = mWorld.getEntityManager().createEntity<T>();
    T* enemy = enemyHandle.getAs<T>();
    if (enemy != nullptr)
    {
        enemy->setRoom(this);
        enemy->setIndex(enemyData.index);
        enemy->setPosition(enemyData.x, enemyData.y);
    }
    mEntities.push_back(enemyHandle);
}

#endif // ROOM_HPP

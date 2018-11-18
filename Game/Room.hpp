#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>

#include "../Engine/Core/World.hpp"

#include "RoomData.hpp"

class Room
{
    public:
        Room(oe::World& world, RoomData& roomData, const oe::EntityHandle& playerHandle);
        ~Room();

        bool update();

        bool hasDoor(RoomData::DoorFlags doorFlag) const;
        unsigned int getRoomIndex(RoomData::DoorFlags doorFlag) const;

        const std::string& getSeed() const;
        unsigned int getIndex() const;

        void addEntity(const oe::EntityHandle& entityHandle);

        const oe::EntityHandle& getPlayerHandle() const;

        typedef std::unique_ptr<Room> Ptr;

    private:
        oe::World& mWorld;
        RoomData& mData;
        const oe::EntityHandle& mPlayerHandle;

        bool mStairs;
        bool mClosedChest;

        std::vector<oe::EntityHandle> mEntities;
};

#endif // ROOM_HPP

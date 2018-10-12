#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>

#include "../Engine/Core/World.hpp"

#include "RoomData.hpp"

class Room
{
    public:
        Room(oe::World& world, RoomData& roomData);
        ~Room();

        typedef std::unique_ptr<Room> Ptr;

    private:
        oe::World& mWorld;
        RoomData& mData;

        std::vector<oe::EntityHandle> mEntities;
};

#endif // ROOM_HPP
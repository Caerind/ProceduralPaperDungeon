#include "Room.hpp"

#include "Background.hpp"

Room::Room(oe::World& world, RoomData& roomData)
    : mWorld(world)
    , mData(roomData)
    , mEntities()
{
    // First load background of the room
	mEntities.push_back(mWorld.getEntityManager().createEntity<Background>(mData));

    // If any add enemy

    // If chest add chest

    // Others things...
}

Room::~Room()
{
}

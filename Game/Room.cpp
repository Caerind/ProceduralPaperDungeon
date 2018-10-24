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

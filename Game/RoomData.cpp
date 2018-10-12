#include "RoomData.hpp"

RoomData::RoomData()
    : mDoorFlags(DoorFlags::None)
{
}

RoomData::~RoomData()
{
}

void RoomData::setDoorFlags(DoorFlags doorFlags)
{
    mDoorFlags = doorFlags;
}

RoomData::DoorFlags RoomData::getDoorFlags() const
{
    return mDoorFlags;
}

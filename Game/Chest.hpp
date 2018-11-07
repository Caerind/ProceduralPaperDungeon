#ifndef CHEST_HPP
#define CHEST_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "RoomData.hpp"

class Chest : public oe::Entity
{
    public:
        Chest(oe::EntityManager& manager, RoomData& roomData);

    private:
        RoomData& mData;
        oe::SpriteComponent mChest;

        static oe::ResourceId mRoomThingsTexture;
};

#endif // CHEST_HPP

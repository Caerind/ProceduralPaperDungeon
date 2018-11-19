#ifndef CHEST_HPP
#define CHEST_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "RoomData.hpp"

class Chest : public oe::Entity
{
    public:
        Chest(oe::EntityManager& manager, RoomData& roomData, const oe::EntityHandle& playerHandle);

        bool isOpen() const;
        void open();

    private:
        RoomData& mData;
        const oe::EntityHandle& mPlayerHandle;
        oe::SpriteComponent mChest;
        bool mOpen;

        static oe::ResourceId mRoomThingsTexture;
};

#endif // CHEST_HPP

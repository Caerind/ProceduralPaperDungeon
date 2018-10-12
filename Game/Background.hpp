#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "RoomData.hpp"

class Background : public oe::Entity
{
    public:
        Background(oe::EntityManager& manager, RoomData& roomData);

    private:
        RoomData& mRoomData;

        oe::SpriteComponent mBackground;
        oe::SpriteComponent mWall;
        std::vector<std::unique_ptr<oe::SpriteComponent>> mDoors;

        static oe::ResourceId mBackgroundTexture;
        static oe::ResourceId mWallTexture;
        static oe::ResourceId mRoomThingsTexture;
};

#endif // BACKGROUND_HPP

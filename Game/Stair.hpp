#ifndef STAIR_HPP
#define STAIR_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

#include "RoomData.hpp"

class Stair : public oe::Entity
{
    public:
        Stair(oe::EntityManager& manager);

    private:
        oe::SpriteComponent mStair;

        static oe::ResourceId mRoomThingsTexture;
};

#endif // STAIR_HPP

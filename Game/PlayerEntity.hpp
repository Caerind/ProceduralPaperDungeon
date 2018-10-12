#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "../Engine/Core/Components/ActionComponent.hpp"

#include "Entity.hpp"

class PlayerEntity : public Entity
{
    public:
        PlayerEntity(oe::EntityManager& manager);
        ~PlayerEntity();

        virtual void update(oe::Time dt);

        void increase();

    private:
        oe::ActionComponent mAction;
};

#endif // PLAYERENTITY_HPP

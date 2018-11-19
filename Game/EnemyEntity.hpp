#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Entity.hpp"
#include "Room.hpp"

class EnemyEntity : public Entity
{
    public:
        enum Type
        {
            Bat,
            Spider,
            Bouftou
        };

        EnemyEntity(oe::EntityManager& manager, Type enemyEntityType);
        ~EnemyEntity();

        void setRoom(Room* room);
        void setIndex(unsigned int index);

        unsigned int getIndexInData() const;
        void updateData();

        bool shoot();

    protected:
        Room* mRoom;
        unsigned int mIndex;
};

#endif // ENEMYENTITY_HPP

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class Entity : public oe::Entity
{
    public:
        Entity(oe::EntityManager& manager);
        ~Entity();

        virtual void update(oe::Time dt);

        int getLife() const;
        int getLifeMax() const;
        int getStrength() const;
        float getMovementSpeed() const;
        float getFireSpeed() const;
        float getFireRange() const;
        float getFireCooldown() const;

        void setLife(int life);
        void reduceLife(int amount);
        void restoreLife(int amount);
        void resetLife();
        void setLifeMax(int lifeMax);
        void setStrength(int strength);
        void setMovementSpeed(float movementSpeed);
        void setFireSpeed(float fireSpeed);
        void setFireRange(float fireRange);
        void setFireCooldown(float fireCooldown);

        virtual bool determineMovement(oe::Vector2& mvt);

		bool tryMove(oe::Time dt, oe::Vector2& mvt);

    protected:
        oe::SpriteComponent mSprite;

        int mLife;
        int mLifeMax;
        int mStrength;
        float mMovementSpeed;
        float mFireSpeed;
        float mFireRange;
        oe::Time mFireLimit;
        oe::Time mFireCooldown;

        static oe::ResourceId mTilesetTexture;
};

#endif // ENTITY_HPP

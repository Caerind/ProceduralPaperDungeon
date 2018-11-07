#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../Engine/Core/Entity.hpp"

#include "../Engine/Core/Components/SpriteComponent.hpp"

class Projectile : public oe::Entity
{
    public:
        Projectile(oe::EntityManager& manager, const oe::Vector2& position, const oe::Vector2& direction, U32 strength, F32 ProjectileSpeed);

		virtual void update(oe::Time dt);

    private:
        oe::SpriteComponent mSprite;
		oe::Vector2 mDirection;
		U32 mStrength;
        F32 mProjectileSpeed;

        static oe::ResourceId mFireTexture;
};
#endif // PROJECTILE_HPP

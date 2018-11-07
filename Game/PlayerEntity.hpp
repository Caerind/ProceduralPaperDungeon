#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "../Engine/Core/Components/ActionComponent.hpp"
#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Core/EntityQuery.hpp"
#include "../Engine/System/ParserXml.hpp"
#include "../Engine/Application/AudioSystem.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "Entity.hpp"

class PlayerEntity : public Entity
{
    public:
        // Inputs
		static oe::ActionInputKey mUp;
		static oe::ActionInputKey mUp2;
		static oe::ActionInputKey mLeft;
		static oe::ActionInputKey mLeft2;
		static oe::ActionInputKey mDown;
		static oe::ActionInputKey mRight;
		static oe::ActionInputMouse mShootInput;
		static void loadInputs();

		bool shoot();

        PlayerEntity(oe::EntityManager& manager);
        ~PlayerEntity();

        virtual void update(oe::Time dt);

        void increase();

    private:
        oe::ActionComponent mAction;

        virtual bool determineMovement(oe::Vector2& mvt);

};

#endif // PLAYERENTITY_HPP

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/World.hpp"

#include "FloorData.hpp"
#include "PlayerEntity.hpp"
#include "RoomData.hpp"
#include "Room.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager, const std::string& seed);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

		const std::string& getSeed() const;

		oe::Window& getWindow();
		oe::View& getView();

    private:
        void checkPlayerAndRoom();
        void checkPlayerAndDoors();

        void goToNextRoom(unsigned int index, const oe::Vector2& playerPosition);
        void goToNextFloor();

        void generateDoorsRects();

	private:
		oe::World mWorld;

		std::string mSeed;
		unsigned int mLevel;

		FloorData::Ptr mFloorData;

        Room::Ptr mCurrentRoom;

        std::array<sf::FloatRect,4> mDoorsRects;

        oe::EntityHandle mPlayerHandle;
};

#endif // GAMESTATE_HPP

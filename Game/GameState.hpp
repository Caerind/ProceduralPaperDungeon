#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/World.hpp"

#include "RoomData.hpp"
#include "Room.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

		oe::Window& getWindow();
		oe::View& getView();

	private:
		oe::World mWorld;
		//oe::ImGuiProfiler mProfiler;

        RoomData mFirstRoomData;
        Room::Ptr mCurrentRoom;

		//oe::EntityHandle playerHandle;
};

#endif // GAMESTATE_HPP

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

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
		oe::Time mDuration;
		oe::ImGuiProfiler mProfiler;

};

#endif // GAMESTATE_HPP

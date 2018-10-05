#include "GameState.hpp"

#include "GameConfig.hpp"

GameState::GameState(oe::StateManager& manager)
	: oe::State(manager)
	, mWorld(manager.getApplication())
{
	mWorld.getRenderSystem().setBackgroundColor(oe::Color::DarkGray);
	mWorld.getRenderSystem().setView(oe::View(0, 0, WINSIZEX, WINSIZEY));
	mWorld.play();
}

bool GameState::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("GameState::handleEvent");

	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		getWindow().screenshot();
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
	{
		if (mProfiler.isVisible())
		{
			mProfiler.hide();
		}
		else
		{
			mProfiler.show();
		}
	}

	return false;
}

bool GameState::update(oe::Time dt)
{
	OE_PROFILE_FUNCTION("GameState::update");

	mDuration += dt;

	mProfiler.draw();

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("GameState::render");

	mWorld.render(target);
}

oe::Window& GameState::getWindow()
{
	return getApplication().getWindow();
}

oe::View& GameState::getView()
{
	return mWorld.getRenderSystem().getView();
}

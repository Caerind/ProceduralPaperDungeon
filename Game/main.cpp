#include "../Engine/Application/Application.hpp"

#include "GameState.hpp"
#include "GameConfig.hpp"

int main()
{
	oe::Application application;

	// Audio Settings
	application.getAudio().setMusicVolume(50.0f);
	application.getAudio().setSoundVolume(50.0f);

	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(WINSIZEX, WINSIZEY), WINTITLE, sf::Style::Close);
	//window.setIcon(ICON_144);
	window.useCustomCursor(WINCURSOR, sf::IntRect(0, 0, 48, 48), sf::Vector2f(24, 24));
	window.setScreenshotPath(WINSCREENSHOTS);
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, WINSIZEX, WINSIZEY)));
	window.applyMainView();
	window.closeOnClosed();

	// Load State
	application.start<GameState>();

	getchar();
	return 0;
}

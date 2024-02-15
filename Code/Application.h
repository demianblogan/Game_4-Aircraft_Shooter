#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Audio/MusicPlayer.h"
#include "Audio/SoundPlayer.h"
#include "States/StateStack.h"
#include "World/Player.h"
#include "World/World.h"

// Application is the main class of the program. It's responsible for
// handling SFML events, updating game states, and rendering
// objects onto the screen. It contains the stack of all states and
// pushes/pops them when it's necessary.
class Application
{
public:
	Application();	
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time deltaTime);
	void UpdateStatistics(sf::Time deltaTime);
	void Render();

	void RegisterStates();

	static sf::Time TIME_PER_FRAME;

	sf::RenderWindow window;
	Player player;
	StateStack stateStack;

	MusicPlayer musicPlayer;
	SoundPlayer soundPlayer;

	TextureHolder textureHolder;
	FontHolder fontHolder;

	sf::Text statisticsText;
	sf::Time statisticsUpdateTime;
	int statisticsNumberOfFrames = 0;
};
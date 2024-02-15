#include "Application.h"

#include <SFML/Window/Event.hpp>

#include "States/GameOverState.h"
#include "States/GameState.h"
#include "States/MenuState.h"
#include "States/PauseState.h"
#include "States/SettingsState.h"
#include "States/TitleState.h"

sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 144); // my monitor supports 144Hz, change this value to your monitor

Application::Application()
	: window(sf::VideoMode(1024, 768), "SFML Application", sf::Style::Close)
	, stateStack(State::Context(window, textureHolder, fontHolder, musicPlayer, soundPlayer, player))
{
	window.setKeyRepeatEnabled(false);

	fontHolder.Load(Font::ID::Main, "Resources/Fonts/Sansation.ttf");

	textureHolder.Load(Texture::ID::TitleScreen , "Resources/Textures/TitleScreen.png");
	textureHolder.Load(Texture::ID::Buttons, "Resources/Textures/Buttons.png");

	statisticsText.setFont(fontHolder.Get(Font::ID::Main));
	statisticsText.setPosition(5, 5);
	statisticsText.setCharacterSize(30);

	RegisterStates();
	stateStack.PushState(State::ID::Title);

	musicPlayer.SetVolume(25);
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			ProcessInput();
			Update(TIME_PER_FRAME);

			if (stateStack.IsEmpty())
				window.close();
		}

		UpdateStatistics(deltaTime);
		Render();
	}
}

void Application::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.HandleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Application::Update(sf::Time deltaTime)
{
	stateStack.Update(deltaTime);
}

void Application::UpdateStatistics(sf::Time deltaTime)
{
	statisticsUpdateTime += deltaTime;
	statisticsNumberOfFrames += 1;

	if (statisticsUpdateTime >= sf::seconds(1))
	{
		statisticsText.setString("FPS: " + std::to_string(statisticsNumberOfFrames));

		statisticsUpdateTime -= sf::seconds(1);
		statisticsNumberOfFrames = 0;
	}
}

void Application::Render()
{
	window.clear();

	stateStack.Draw();

	window.setView(window.getDefaultView());
	window.draw(statisticsText);

	window.display();
}

void Application::RegisterStates()
{
	stateStack.RegisterState<TitleState>(State::ID::Title);
	stateStack.RegisterState<MenuState>(State::ID::Menu);
	stateStack.RegisterState<GameState>(State::ID::Game);
	stateStack.RegisterState<PauseState>(State::ID::Pause);
	stateStack.RegisterState<SettingsState>(State::ID::Settings);
	stateStack.RegisterState<GameOverState>(State::ID::GameOver);
}
#include "MenuState.h"

#include <SFML/Window/Event.hpp>

#include "../Audio/MusicPlayer.h"
#include "../GUI/Button.h"
#include "../Utilities/Utilities.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& titleScreenTexture = context.textureHolder->Get(Texture::ID::TitleScreen);
	backgroundSprite.setTexture(titleScreenTexture);

	auto playButtonPtr = std::make_shared<GUI::Button>(context);
	playButtonPtr->setPosition(380, 300);
	playButtonPtr->SetText("Play");
	playButtonPtr->SetCallback(
		[this]()
		{
			RequestStackPop();
			RequestStackPush(State::ID::Game);
		}
	);

	auto settingsButtonPtr = std::make_shared<GUI::Button>(context);
	settingsButtonPtr->setPosition(380, 350);
	settingsButtonPtr->SetText("Settings");
	settingsButtonPtr->SetCallback(
		[this]()
		{
			RequestStackPush(State::ID::Settings);
		}
	);

	auto exitButtonPtr = std::make_shared<GUI::Button>(context);
	exitButtonPtr->setPosition(380, 400);
	exitButtonPtr->SetText("Exit");
	exitButtonPtr->SetCallback(
		[this]()
		{
			RequestStackPop();
		}
	);

	GUI_container.AddComponent(playButtonPtr);
	GUI_container.AddComponent(settingsButtonPtr);
	GUI_container.AddComponent(exitButtonPtr);

	context.musicPlayer->Play(Music::ID::MenuTheme);
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	GUI_container.HandleEvent(event);
	return false;
}

bool MenuState::Update(sf::Time deltaTime)
{
	return true;
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(GUI_container);
}
#include "PauseState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "../Audio/MusicPlayer.h"
#include "../GUI/Button.h"
#include "../Utilities/Utilities.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Font& font = context.fontHolder->Get(Font::ID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	pauseText.setFont(font);
	pauseText.setString("Game Paused");
	pauseText.setCharacterSize(70);
	CenterOrigin(pauseText);
	pauseText.setPosition(windowSize.x * 0.5f, windowSize.y * 0.4f);

	auto returnToGameButtonPtr = std::make_shared<GUI::Button>(context);
	returnToGameButtonPtr->setPosition(windowSize.x * 0.5f - 100, windowSize.y * 0.4f + 75);
	returnToGameButtonPtr->SetText("Return");
	returnToGameButtonPtr->SetCallback(
		[this]()
		{
			RequestStackPop();
		}
	);

	auto backToMenuButtonPtr = std::make_shared<GUI::Button>(context);
	backToMenuButtonPtr->setPosition(windowSize.x * 0.5f - 100, windowSize.y * 0.4f + 125);
	backToMenuButtonPtr->SetText("Back to menu");
	backToMenuButtonPtr->SetCallback(
		[this]()
		{
			RequestStateClear();
			RequestStackPush(State::ID::Menu);
		}
	);

	GUI_container.AddComponent(returnToGameButtonPtr);
	GUI_container.AddComponent(backToMenuButtonPtr);

	GetContext().musicPlayer->SetPaused(true);
}

PauseState::~PauseState()
{
	GetContext().musicPlayer->SetPaused(false);
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	GUI_container.HandleEvent(event);
	return false;
}

bool PauseState::Update(sf::Time deltaTime)
{
	return false;
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseText);
	window.draw(GUI_container);
}
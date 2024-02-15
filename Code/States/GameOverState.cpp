#include "GameOverState.h"
#include "../World/Player.h"
#include "../Utilities/Utilities.h"
#include <SFML/Graphics/RectangleShape.hpp>

GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Font& font = context.fontHolder->Get(Font::ID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	gameOverText.setFont(font);
	if (context.player->GetMissionStatus() == Player::MissionStatus::Failure)
		gameOverText.setString("Mission failed!");
	else
		gameOverText.setString("Mission successful!");

	gameOverText.setCharacterSize(70);
	CenterOrigin(gameOverText);
	gameOverText.setPosition(windowSize.x * 0.5f, windowSize.y * 0.4f);
}

bool GameOverState::HandleEvent(const sf::Event& event)
{
	return false;
}


bool GameOverState::Update(sf::Time deltaTime)
{
	// Show state for 3 seconds, after return to the main menu:
	elapsedTime += deltaTime;
	if (elapsedTime > sf::seconds(3))
	{
		RequestStateClear();
		RequestStackPush(State::ID::Menu);
	}

	return false;
}

void GameOverState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background:
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText);
}
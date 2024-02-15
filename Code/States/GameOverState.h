#pragma once

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "../GUI/Container.h"

// Game over state appears in two scenarios:
// 1) When you have died in the game state
// 2) When you have reached the end of the level
// This state just shows you some information about
// the mission status. In both scenarios the game is over,
// because the game has only one level.
class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context context);

	virtual bool HandleEvent(const sf::Event& event);
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	sf::Text gameOverText;
	sf::Time elapsedTime = sf::Time::Zero;
};
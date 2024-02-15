#pragma once

#include "State.h"
#include "../World/World.h"

// Game state is the main state of the game, because in it you actually
// "play" the game as a player who controls an airship. This state has its
// own world and player.
class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	World world;
	Player& player;
};
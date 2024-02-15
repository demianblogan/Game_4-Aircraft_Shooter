#include "Player.h"

#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include "Aircraft.h"
#include "../Commands/CommandQueue.h"
#include "../SceneNodes/Category.h"

using namespace std::placeholders;

// Helper functor for binding actions.
struct AircraftMover
{
	AircraftMover(float x, float y)
		: velocity(x, y)
	{ }

	void operator()(Aircraft& aircraft, sf::Time) const
	{
		aircraft.Accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	keyBindings[sf::Keyboard::Left] = Player::Action::MoveLeft;
	keyBindings[sf::Keyboard::Right] = Player::Action::MoveRight;
	keyBindings[sf::Keyboard::Up] = Player::Action::MoveUp;
	keyBindings[sf::Keyboard::Down] = Player::Action::MoveDown;
	keyBindings[sf::Keyboard::Space] = Player::Action::Fire;
	keyBindings[sf::Keyboard::M] = Player::Action::LaunchMissile;

	actionBindings[Player::Action::MoveLeft].action = GetDerivedAction<Aircraft>(AircraftMover(-MOVE_SPEED, 0));
	actionBindings[Player::Action::MoveRight].action = GetDerivedAction<Aircraft>(AircraftMover(MOVE_SPEED, 0));
	actionBindings[Player::Action::MoveUp].action = GetDerivedAction<Aircraft>(AircraftMover(0, -MOVE_SPEED));
	actionBindings[Player::Action::MoveDown].action = GetDerivedAction<Aircraft>(AircraftMover(0, MOVE_SPEED));
	actionBindings[Player::Action::Fire].action = GetDerivedAction<Aircraft>(
		[](Aircraft& aircraft, sf::Time)
		{
			aircraft.Fire();
		});
	actionBindings[Player::Action::LaunchMissile].action = GetDerivedAction<Aircraft>(
		[](Aircraft& aircraft, sf::Time)
		{
			aircraft.LaunchMissile();
		});

	// Assign all categories to player's aircraft category:
	for (auto& actionBinding : actionBindings)
		actionBinding.second.category = Category::PlayerAircraft;
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commandQueue)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, and trigger command if so
		auto found = keyBindings.find(event.key.code);
		if (found != keyBindings.end() && !IsRealtimeAction(found->second))
			commandQueue.Push(actionBindings[found->second]);
	}
}

void Player::HandleRealtimeInput(CommandQueue& commandQueue)
{
	for (auto& [key, action] : keyBindings)
	{
		if (sf::Keyboard::isKeyPressed(key) && IsRealtimeAction(action))
			commandQueue.Push(actionBindings[action]);
	}
}

void Player::AssignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action:
	for (auto iter = keyBindings.begin(), end = keyBindings.end(); iter != end;)
	{
		if (iter->second == action)
			keyBindings.erase(iter++);
		else
			++iter;
	}

	keyBindings[key] = action;
}

sf::Keyboard::Key Player::GetAssignedKey(Action action) const
{
	for (auto& [keyInMap, actionInMap] : keyBindings)
	{
		if (actionInMap == action)
			return keyInMap;
	}

	return sf::Keyboard::Unknown;
}

void Player::SetMissionStatus(MissionStatus status)
{
	currentMissionStatus = status;
}

Player::MissionStatus Player::GetMissionStatus() const
{
	return currentMissionStatus;
}

bool Player::IsRealtimeAction(Action action)
{
	switch (action)
	{
	case Player::Action::MoveLeft:
	case Player::Action::MoveRight:
	case Player::Action::MoveUp:
	case Player::Action::MoveDown:
	case Player::Action::Fire:
		return true;

	default:
		return false;
	}
}
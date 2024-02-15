#pragma once

#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Commands/Command.h"

class CommandQueue;

// Player class is a class that encapsulates all logic a player can do
// to the aircraft. Player can move it, shoot with two different ways.
// Also this class tracks the missions status (if player's died or passed the level).
class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		Count
	};

	enum class MissionStatus
	{
		Running,
		Success,
		Failure
	};

	Player();

	void HandleEvent(const sf::Event& event, CommandQueue& commandQueue);
	void HandleRealtimeInput(CommandQueue& commandQueue);

	void AssignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key GetAssignedKey(Action action) const;

	void SetMissionStatus(MissionStatus status);
	MissionStatus GetMissionStatus() const;

private:
	static bool IsRealtimeAction(Action action);

	static constexpr float MOVE_SPEED = 200.0f;

	std::map<sf::Keyboard::Key, Action> keyBindings;
	std::map<Action, Command> actionBindings;
	MissionStatus currentMissionStatus = MissionStatus::Running;
};
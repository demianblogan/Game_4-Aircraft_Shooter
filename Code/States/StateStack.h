#pragma once

#include <functional>
#include <map>
#include <vector>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "State.h"

// Some states can be "above" other state. For example if there is a state "Game" when
// you're controlling a spaceship, you can pause the game. It means, that there will
// be a pause state above game state. If we want some states continue their work "in the background",
// we must push new states onto the stack and pop them as soon as we close them.
// So StateStack class implement ADT Stack on the top of std::vector class.
class StateStack : private sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);

	template <typename T>
	void RegisterState(State::ID stateID)
	{
		factories[stateID] = [this]()
			{
				return State::Pointer(new T(*this, context));
			};
	}

	void HandleEvent(const sf::Event& event);
	void Update(sf::Time deltaTime);
	void Draw();

	void PushState(State::ID stateID);
	void PopState();
	void ClearStates();

	bool IsEmpty() const;

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, State::ID stateID = State::ID::None);

		Action action;
		State::ID stateID;
	};

	State::Pointer CreateState(State::ID stateID);
	void ApplyPendingChanges();

	std::vector<State::Pointer> stack;
	std::vector<PendingChange> pendingChangesList;

	State::Context context;
	std::map<State::ID, std::function<State::Pointer()>> factories;
};
#include "StateStack.h"

State::Pointer StateStack::CreateState(State::ID stateID)
{
	auto foundIter = factories.find(stateID);
	assert(foundIter != factories.end());

	return foundIter->second();
}

void StateStack::ApplyPendingChanges()
{
	for (const PendingChange& change : pendingChangesList)
	{
		switch (change.action)
		{
		case Action::Push:
			stack.push_back(CreateState(change.stateID));
			break;

		case Action::Pop:
			stack.pop_back();
			break;

		case Action::Clear:
			stack.clear();
			break;
		}
	}

	pendingChangesList.clear();
}

StateStack::StateStack(State::Context context)
	: context(context)
{ }

void StateStack::HandleEvent(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto stateIter = stack.rbegin(), rend = stack.rend(); stateIter != rend; ++stateIter)
		if (!(*stateIter)->HandleEvent(event))
			break;

	ApplyPendingChanges();
}

void StateStack::Update(sf::Time deltaTime)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto stateIter = stack.rbegin(), rend = stack.rend(); stateIter != rend; ++stateIter)
		if (!(*stateIter)->Update(deltaTime))
			break;

	ApplyPendingChanges();
}

void StateStack::Draw()
{
	// Draw all active states from bottom to top
	for (State::Pointer& state : stack)
		state->Draw();
}

void StateStack::PushState(State::ID stateID)
{
	pendingChangesList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::PopState()
{
	pendingChangesList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates()
{
	pendingChangesList.push_back(PendingChange(Action::Clear));
}

bool StateStack::IsEmpty() const
{
	return stack.empty();
}

StateStack::PendingChange::PendingChange(Action action, State::ID stateID)
	: action(action)
	, stateID(stateID)
{ }
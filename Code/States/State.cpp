#include "State.h"

#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, Player& player)
	: window(&window)
	, textureHolder(&textureHolder)
	, fontHolder(&fontHolder)
	, musicPlayer(&musicPlayer)
	, soundPlayer(&soundPlayer)
	, player(&player)
{ }

State::State(StateStack& stack, Context context)
	: stack(&stack)
	, context(context)
{ }

State::~State()
{ }

void State::RequestStackPush(State::ID stateID)
{
	stack->PushState(stateID);
}

void State::RequestStackPop()
{
	stack->PopState();
}

void State::RequestStateClear()
{
	stack->ClearStates();
}

State::Context State::GetContext() const
{
	return context;
}
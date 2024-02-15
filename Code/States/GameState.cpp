#include "GameState.h"

#include "../Audio/MusicPlayer.h"
#include "../World/Player.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, world(*context.window, *context.fontHolder, *context.soundPlayer)
	, player(*context.player)
{
	player.SetMissionStatus(Player::MissionStatus::Running);
	context.musicPlayer->Play(Music::ID::MissionTheme);
}

bool GameState::HandleEvent(const sf::Event& event)
{
	// Game input handling:
	CommandQueue& commandQueue = world.GetCommandQueue();
	player.HandleEvent(event, commandQueue);

	// If escape has been pressed, then trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		RequestStackPush(State::ID::Pause);

	return true;
}

bool GameState::Update(sf::Time deltaTime)
{
	world.Update(deltaTime);

	if (!world.HasAlivePlayer())
	{
		player.SetMissionStatus(Player::MissionStatus::Failure);
		RequestStackPush(State::ID::GameOver);
	}
	else if (world.HasPlayerReachedEnd())
	{
		player.SetMissionStatus(Player::MissionStatus::Success);
		RequestStackPush(State::ID::GameOver);
	}

	CommandQueue& commandQueue = world.GetCommandQueue();
	player.HandleRealtimeInput(commandQueue);

	return true;
}

void GameState::Draw()
{
	world.Draw();
}
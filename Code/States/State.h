#pragma once

#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"

class Player;
class StateStack;
class MusicPlayer;
class SoundPlayer;

// Game has a few main states: title screen state, main menu state, settings menu state, etc.
// Every state encapsulates some logic that happens in it. But all states must have access to
// "Context" - structure with all main resource folders, pointer to the window and the player.
// All states have some identical behaviour, so "State" class is a base abstract class for all of them.
class State
{
public:
	using Pointer = std::unique_ptr<State>;
	
	enum class ID
	{
		None,
		Title,
		Menu,
		Game,
		Pause,
		Settings,
		GameOver
	};

	// All states, when are being created, must have its own "Context" object to play sounds, render
	// textures and fonts, to operate with the player and window. It's a simple aggregate structure.
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, Player& player);
		
		sf::RenderWindow* window;
		TextureHolder* textureHolder;
		FontHolder* fontHolder;
		MusicPlayer* musicPlayer;
		SoundPlayer* soundPlayer;
		Player* player;
	};

	State(StateStack& stack, Context context);
	virtual ~State();

	virtual bool HandleEvent(const sf::Event& event) = 0;
	virtual bool Update(sf::Time deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	void RequestStackPush(State::ID stateID);
	void RequestStackPop();
	void RequestStateClear();

	Context GetContext() const;

private:
	StateStack* stack;
	Context context;
};
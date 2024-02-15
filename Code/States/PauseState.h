#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "../GUI/Container.h"

// Pause state is a pause that you can make when playing the game. You can go back
// to the game or quit to the main menu from pause state. Pause has its small
// background texture, some text and a menu of 2 items: go back to the game & quit to
// the main menu.
class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);
	~PauseState();

	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	sf::Sprite backgroundSprite;
	sf::Text pauseText;
	GUI::Container GUI_container;
};
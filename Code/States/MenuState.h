#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "../GUI/Container.h"

// Menu state is the main menu of the game. It has a background texture
// and a simple menu that contains 3 items: play the game, go to the settings,
// and quit the game.
class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);
	
	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	sf::Sprite backgroundSprite;
	GUI::Container GUI_container;
};
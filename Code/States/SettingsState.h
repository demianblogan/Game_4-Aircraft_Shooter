#pragma once

#include <array>

#include <SFML/Graphics/Sprite.hpp>

#include "State.h"

#include "../GUI/Container.h"
#include "../GUI/Button.h"
#include "../GUI/Label.h"
#include "../World/Player.h"

// Settings state is a menu with a few settings and background texture.
// In settings you can bind keys with player actions, like moving directions
// and firing.
class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	void UpdateLabels();
	void AddButtonAndLabel(Player::Action action, float y, const std::string& text, Context context);

	sf::Sprite backgroundSprite;
	GUI::Container GUI_container;
	std::array<GUI::Button::Pointer, int(Player::Action::Count)> bindingButtons;
	std::array<GUI::Label::Pointer, int(Player::Action::Count)> bindingLabels;
};